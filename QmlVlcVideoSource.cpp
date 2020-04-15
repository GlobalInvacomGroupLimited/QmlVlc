/*******************************************************************************
* Copyright © 2015, Sergey Radionov <rsatom_gmail.com>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.

* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "QmlVlcVideoSource.h"

#include <memory>
#include <QtCore/QMutex>
#include <QtCore/QThread>

#include <QtQuick/QQuickWindow>

#include "QmlVlcTextureNode.h"


QmlVlcVideoSource::QmlVlcVideoSource()
    : m_videoOutput( nullptr )
{
    setFlag(ItemHasContents, true);
}
QmlVlcVideoSource::~QmlVlcVideoSource()
{
    m_videoOutput->terminate();
    m_videoOutput->wait();
}

void QmlVlcVideoSource::classBegin( const std::shared_ptr<VLC::MediaPlayer>& player )
{

    m_videoOutput.reset( new QmlVlcOpenGlOutput( ) );

    QObject::connect(m_videoOutput.data(), SIGNAL(framesDisplayed()), this,  SIGNAL(displayedFrames()));

    m_videoOutput->classBegin( player );
}

void QmlVlcVideoSource::ready()
{

    m_videoOutput->surface = new QOffscreenSurface();
    m_videoOutput->context->format().setSwapBehavior(QSurfaceFormat::TripleBuffer);
    m_videoOutput->surface->setFormat(m_videoOutput->context->format());
    m_videoOutput->surface->create();

    m_videoOutput->moveToThread(m_videoOutput.get());

    m_videoOutput->init(size().toSize());

    m_videoOutput->start();
    update();
}

void QmlVlcVideoSource::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);

    if(m_videoOutput) {
        m_videoOutput->updateSize(newGeometry.size().toSize());
    }
}

QSGNode *QmlVlcVideoSource::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QmlVlcTextureNode *node = static_cast<QmlVlcTextureNode *>(oldNode);

    if (!m_videoOutput->context) {
        QOpenGLContext *current = window()->openglContext();
        // Some GL implementations requres that the currently bound context is
        // made non-current before we set up sharing, so we doneCurrent here
        // and makeCurrent down below while setting up our own context.
        current->doneCurrent();

        m_videoOutput->context = new QOpenGLContext();
        m_videoOutput->context->setFormat(current->format());
        m_videoOutput->context->setShareContext(current);
        m_videoOutput->context->create();
        m_videoOutput->context->moveToThread(m_videoOutput.get());

        current->makeCurrent(window());

        QMetaObject::invokeMethod(this, "ready");
        return nullptr;
    }

    if (!node) {
        node = new QmlVlcTextureNode(window());

        /* Set up connections to get the production of FBO textures in sync with vsync on the
         * rendering thread.
         *
         * When a new texture is ready on the rendering thread, we use a direct connection to
         * the texture node to let it know a new texture can be used. The node will then
         * emit pendingNewTexture which we bind to QQuickWindow::update to schedule a redraw.
         *
         * When the scene graph starts rendering the next frame, the prepareNode() function
         * is used to update the node with the new texture. Once it completes, it emits
         * textureInUse() which we connect to the FBO rendering thread's getVideoFrame() to have
         * it start producing content into its current "back buffer".
         *
         * This FBO rendering pipeline is throttled by vsync on the scene graph rendering thread.
         */

        connect(m_videoOutput.data(), &QmlVlcOpenGlOutput::textureReady, node, &QmlVlcTextureNode::newTexture, Qt::DirectConnection);
        connect(node, &QmlVlcTextureNode::pendingNewTexture, window(), &QQuickWindow::update, Qt::QueuedConnection);
        connect(window(), &QQuickWindow::beforeRendering, node, &QmlVlcTextureNode::prepareNode, Qt::DirectConnection);
        connect(node, &QmlVlcTextureNode::textureInUse, m_videoOutput.data(), &QmlVlcOpenGlOutput::getVideoFrame, Qt::QueuedConnection);
    }

    node->setTextureCoordinatesTransform(QSGSimpleTextureNode::MirrorVertically);
    node->setRect(boundingRect());

    return node;
}


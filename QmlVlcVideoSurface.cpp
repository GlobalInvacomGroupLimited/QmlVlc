/*******************************************************************************
* Copyright © 2014-2015, Sergey Radionov <rsatom_gmail.com>
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

#include "QmlVlcVideoSurface.h"

#include "QmlVlcVideoFrame.h"
#include "SGVlcVideoNode.h"

QmlVlcVideoSurface::QmlVlcVideoSurface()
    : m_fillMode( PreserveAspectFit ), m_aspectRatio( R_16_9 ), m_source( nullptr ), m_frameUpdated( false )
{
    setFlag( QQuickItem::ItemHasContents, true );
}

QmlVlcVideoSurface::~QmlVlcVideoSurface()
{
    setSource( 0 );
}

void QmlVlcVideoSurface::setFillMode( FillMode m )
{
    if( m_fillMode == m )
        return;

    m_fillMode = m;

    update();

    emit fillModeChanged( m );
}


int QmlVlcVideoSurface::aspectRatio() const
{
    return m_aspectRatio;
}

void QmlVlcVideoSurface::setAspectRatio(int aspectRatio)
{
    if (m_aspectRatio == aspectRatio)
        return;

    m_aspectRatio = QmlVlcVideoSurface::Ratio(aspectRatio);

    update();

    emit aspectRatioChanged();
}

int QmlVlcVideoSurface::cropRatio() const
{
    return m_cropRatio;
}

void QmlVlcVideoSurface::setCropRatio(int cropRatio)
{
    if (m_cropRatio == cropRatio)
        return;

    m_cropRatio = QmlVlcVideoSurface::Ratio(cropRatio);

    update();

    emit cropRatioChanged();
}

QmlVlcVideoSource* QmlVlcVideoSurface::source() const
{
    return m_source;
}

void QmlVlcVideoSurface::setSource( QmlVlcVideoSource* source )
{
    if( source == m_source )
        return;

    if( m_source )
        m_source->unregisterVideoSurface( this );

    m_source = source;

    if( m_source )
        m_source->registerVideoSurface( this );

    Q_EMIT sourceChanged();
}

QSGNode* QmlVlcVideoSurface::updatePaintNode( QSGNode* oldNode,
                                            UpdatePaintNodeData *data)
{
    Q_UNUSED(data)

    SGVlcVideoNode* node = static_cast<SGVlcVideoNode*>( oldNode );
    if( !m_frame ) {
        delete node;
        return 0;
    }

    if( !node )
        node = new SGVlcVideoNode;

    QRectF outRect( 0, 0, width(), height() );
    QRectF srcRect( 0, 0, 1., 1. );

    if( Stretch != fillMode() ) {
        const uint16_t fw = m_frame->width;
        const uint16_t fh = m_frame->height;

        qreal frameAspectTmp = qreal( fw ) / fh;
        QSizeF aspectRatioSize = ratioSize(m_aspectRatio);
        if (aspectRatioSize.width() != 0 && aspectRatioSize.height() != 0) {
            frameAspectTmp = aspectRatioSize.width() / aspectRatioSize.height();
        }
        QSizeF cropRatioSize = ratioSize(m_cropRatio);
        if (cropRatioSize.width() != 0 && cropRatioSize.height() != 0) {
            const qreal cropAspect = cropRatioSize.width() / cropRatioSize.height();

            if (frameAspectTmp > cropAspect) {
                srcRect.setX((1. - cropAspect / frameAspectTmp) / 2);
                srcRect.setWidth(1. - srcRect.x() - srcRect.x());
            } else if (frameAspectTmp < cropAspect) {
                srcRect.setY((1. - frameAspectTmp / cropAspect) / 2);
                srcRect.setHeight(1. - srcRect.y() - srcRect.y());
            }

            frameAspectTmp = cropAspect;
        }
        const qreal itemAspect = width() / height();
        const qreal frameAspect = frameAspectTmp;

        if( PreserveAspectFit == fillMode() ) {
            qreal outWidth = width();
            qreal outHeight = height();
            if( frameAspect > itemAspect )
                outHeight = outWidth / frameAspect;
            else if( frameAspect < itemAspect )
                outWidth = outHeight * frameAspect;

            outRect = QRectF( ( width() - outWidth ) / 2, ( height() - outHeight ) / 2,
                               outWidth, outHeight );
        } else if( PreserveAspectCrop == fillMode() ) {
            if( frameAspect > itemAspect ) {
                srcRect.setX( ( 1. - itemAspect / frameAspect ) / 2 );
                srcRect.setWidth( 1. - srcRect.x() - srcRect.x() );
            } else if( frameAspect < itemAspect ) {
                srcRect.setY( ( 1. - frameAspect / itemAspect ) / 2 );
                srcRect.setHeight( 1. - srcRect.y() - srcRect.y() );
            }
        }
    }

    if( m_frameUpdated ) {
        node->setFrame( m_frame );
        m_frameUpdated = false;
    }
    node->setRect( outRect, srcRect );

    return node;
}

void QmlVlcVideoSurface::presentFrame( const std::shared_ptr<const QmlVlcI420Frame>& frame )
{
    m_frame = frame;
    m_frameUpdated = true;
    update();
}

QSizeF QmlVlcVideoSurface::ratioSize(const QmlVlcVideoSurface::Ratio &ratio)
{
    switch (ratio) {
    case QmlVlcVideoSurface::R_16_9:
        return QSizeF(16, 9);
        break;
    case QmlVlcVideoSurface::R_16_10:
        return QSizeF(16, 10);
        break;
    case QmlVlcVideoSurface::R_185_100:
        return QSizeF(185, 100);
        break;
    case QmlVlcVideoSurface::R_221_100:
        return QSizeF(221, 100);
        break;
    case QmlVlcVideoSurface::R_235_100:
        return QSizeF(235, 100);
        break;
    case QmlVlcVideoSurface::R_239_100:
        return QSizeF(239, 100);
        break;
    case QmlVlcVideoSurface::R_4_3:
        return QSizeF(4, 3);
        break;
    case QmlVlcVideoSurface::R_5_4:
        return QSizeF(5, 4);
        break;
    case QmlVlcVideoSurface::R_5_3:
        return QSizeF(5, 3);
        break;
    case QmlVlcVideoSurface::R_1_1:
        return QSizeF(1, 1);
        break;
    case QmlVlcVideoSurface::Original:
    case QmlVlcVideoSurface::Ignore:
    default:
        return QSizeF(0, 0);
        break;
    }

    return QSizeF(0, 0);
}




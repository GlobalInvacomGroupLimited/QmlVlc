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

#pragma once

#include <memory>

#include <QtQml/qqml.h>
#include <QQmlParserStatus>
#include <QSGNode>
#include <QQuickItem>

#include <libvlcpp/vlcpp/vlc.hpp>

#include "QmlVlcOpenGlOutput.h"

class QmlVlcVideoSource : public QQuickItem
{
    Q_OBJECT
    Q_INTERFACES( QQmlParserStatus )

    Q_PROPERTY( int majorVerion READ get_majorVersion WRITE set_majorVersion )
    Q_PROPERTY( int minorVerion READ get_minorVersion WRITE set_minorVersion )


public Q_SLOTS:
    void ready();


public:
    QmlVlcVideoSource( );
    ~QmlVlcVideoSource( );

    using QQmlParserStatus::classBegin;
    virtual void classBegin( const std::shared_ptr<VLC::MediaPlayer>& player );


signals:
    void displayedFrames();



protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

private:
    QScopedPointer<QmlVlcOpenGlOutput> m_videoOutput;

    int majorVerion;
    int minorVerion;

    using QQuickItem::geometryChanged;
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    int get_majorVersion() {return majorVerion;}
    int get_minorVersion() {return minorVerion;}

    void set_majorVersion(int version) {majorVerion = version; qDebug() << "**** MajorVersion" + QString(majorVerion);  }
    void set_minorVersion(int version) {minorVerion = version; qDebug() << "**** MinorVersion" + QString(minorVerion);}
};

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

#pragma once

#include <cassert>
#include <memory>
#include <deque>

#include <QQmlParserStatus>

#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>

#ifndef Q_MOC_RUN
#include <libvlcpp/vlcpp/vlc.hpp>
#endif // Q_MOC_RUN

#include "QmlVlcVideoFrame.h"

class QmlVlcVideoOutput : public QObject
{
    Q_OBJECT
public:
    explicit QmlVlcVideoOutput( QObject* parent = 0 );

    void classBegin( const std::shared_ptr<VLC::MediaPlayer>& player );
    void init();
    ~QmlVlcVideoOutput();

    std::shared_ptr<const QmlVlcI420Frame> renderFrame() const
        { return m_renderFrame; }

    QAbstractVideoSurface* videoSurface() const
        { return m_videoSurface; }
    void setVideoSurface( QAbstractVideoSurface* s );

signals:
    void framesDisplayed();

private:
    Q_INVOKABLE void frameUpdated();

    Q_INVOKABLE void updateSurfaceFormat( const QVideoSurfaceFormat& newFormat );
    Q_INVOKABLE void cleanupVideoSurface();

    void initVideoSurface( const QVideoSurfaceFormat& format );

private:
    //for libvlc_video_set_format_callbacks
    virtual unsigned video_format_cb( char *chroma,
                                      unsigned *width, unsigned *height,
                                      unsigned *pitches, unsigned *lines );
    virtual void video_cleanup_cb();
    //end (for libvlc_video_set_format_callbacks)

    //for libvlc_video_set_callbacks
    virtual void* video_lock_cb( void **planes );
    virtual void  video_unlock_cb( void *picture, void *const *planes );
    virtual void  video_display_cb( void *picture );
    //end (for libvlc_video_set_callbacks)

private:
    std::shared_ptr<VLC::MediaPlayer> m_player;

    std::deque<std::shared_ptr<QmlVlcI420Frame> > m_frames;
    std::list<std::shared_ptr<QmlVlcI420Frame> > m_lockedFrames;
    std::shared_ptr<QmlVlcI420Frame> m_renderFrame;

    QVideoSurfaceFormat m_surfaceFormat;
    QAbstractVideoSurface* m_videoSurface;

    int frameCounter;
    bool emitframesDisplayed;
};

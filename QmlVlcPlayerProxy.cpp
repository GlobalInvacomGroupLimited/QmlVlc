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

#include <unistd.h>
#include "QmlVlcPlayerProxy.h"
#include "QmlVlcConfig.h"

#include <QDebug>
#include <QCoreApplication>

QmlVlcPlayerProxy::QmlVlcPlayerProxy( QObject* parent )
    : QmlVlcVideoSource( parent ), m_player( nullptr )
{
    qRegisterMetaType<QmlVlcPlayerProxy::State>( "QmlVlcPlayerProxy::State" );

    m_errorTimer.setInterval( 1000 );
    m_errorTimer.setSingleShot( true );

    connect( this, SIGNAL( mediaPlayerEncounteredError() ),
             &m_errorTimer, SLOT( start() ) );
    connect( &m_errorTimer, SIGNAL( timeout() ),
             this, SLOT( currentItemEndReached() ) );

    connect( this, SIGNAL( mediaPlayerEndReached() ),
             &m_errorTimer, SLOT( stop() ) );
    connect( this, SIGNAL( mediaPlayerEndReached() ),
             this, SLOT( currentItemEndReached() ) );

    connect( this, SIGNAL( mediaPlayerMediaChanged() ),
             &m_errorTimer, SLOT( stop() ) );
    //connect( this, &QmlVlcPlayerProxy::mediaPlayerMediaChanged,
    //         get_subtitle(), &QmlVlcSubtitle::eraseLoaded );

    //connect( get_audio(), SIGNAL( volumeChanged() ),
    //         this, SIGNAL( volumeChanged() ) );
}

void QmlVlcPlayerProxy::classBegin( const std::shared_ptr<VLC::MediaPlayer>& player )
{
    //player().register_callback( this );
    m_player   = player;

    m_audio.classBegin(player);

    QmlVlcVideoSource::classBegin( player );
}

void QmlVlcPlayerProxy::componentComplete()
{
}

void QmlVlcPlayerProxy::classEnd()
{
    m_audio.classEnd();
}

QmlVlcPlayerProxy::~QmlVlcPlayerProxy()
{
    classEnd();
}

void QmlVlcPlayerProxy::currentItemEndReached()
{

}

QString QmlVlcPlayerProxy::get_vlcVersion()
{
    return QString::fromLatin1( libvlc_get_version() );
}

void QmlVlcPlayerProxy::play( const QString& mrl )
{
    VLC::MediaPlayer& p = player();

    auto media = VLC::Media( QmlVlcConfig::instance().getLibvlcInstance(), mrl.toUtf8().constData(), VLC::Media::FromLocation );

    p.setMedia( media );

    p.play();
}

void QmlVlcPlayerProxy::play()
{
    player().play();
}

void QmlVlcPlayerProxy::pause()
{
    player().setPause(true);
}

void QmlVlcPlayerProxy::unpause()
{
    player().setPause(false);
}

void QmlVlcPlayerProxy::togglePause()
{
    player().pause();
}

void QmlVlcPlayerProxy::stop()
{
    player().stop();
}

QString QmlVlcPlayerProxy::get_mrl()
{
    std::string mrl = player().media()->mrl();
    return QString::fromUtf8( mrl.data(), mrl.size() );
}

void QmlVlcPlayerProxy::set_mrl( const QString& mrl )
{
    play( mrl );
}

bool QmlVlcPlayerProxy::get_playing()
{
    return player().isPlaying();
}

double QmlVlcPlayerProxy::get_length()
{
    return static_cast<double>( player().length() );
}

double QmlVlcPlayerProxy::get_position()
{
    return player().position();
}

void QmlVlcPlayerProxy::set_position( double pos )
{
    player().setPosition( static_cast<float>( pos ) );
}

double QmlVlcPlayerProxy::get_time()
{
    return static_cast<double>( player().time() );
}

void QmlVlcPlayerProxy::set_time( double t )
{
    player().setTime( static_cast<libvlc_time_t>( t ) );
}

QmlVlcPlayerProxy::State QmlVlcPlayerProxy::get_state()
{
    return static_cast<State>( player().state() );
}

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

QmlVlcPlayerProxy::QmlVlcPlayerProxy( QObject* parent ) : QmlVlcVideoSource( parent ),
    m_player( nullptr ), h_onPlaying( nullptr ), h_onStopped( nullptr ), playing( false )
{
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

void QmlVlcPlayerProxy::classBegin( )
{
    // Get the instance of libVLC
    m_libvlc = QmlVlcConfig::instance( ).getLibvlcInstance( );

    auto n_player = std::make_shared<VLC::MediaPlayer>( *(m_libvlc  ) );

    m_player   = n_player;

    h_onPlaying = player().eventManager().onPlaying( [this](){
        playing = true;
        Q_EMIT playingChanged(); } );

    h_onStopped = player().eventManager().onStopped( [this](){
        playing = false;
        Q_EMIT playingChanged(); } );

    h_onEncounteredError = player().eventManager().onEncounteredError( [this](){
        Q_EMIT encounteredError(); } );


    player().setFecStatsCallbacks( [this]( void * stats  ) {
        FecStats * fecStats_p = ( FecStats *) stats;

        FecStats fecStats;
        fecStats.blockNumber  = fecStats_p->blockNumber;
        fecStats.missingPkts  = fecStats_p->missingPkts;
        fecStats.receivedPkts = fecStats_p->receivedPkts;
        fecStats.recovered    = fecStats_p->recovered;

        Q_EMIT gotStats( fecStats );
    } );

    m_audio.classBegin(n_player);

    QmlVlcVideoSource::classBegin( n_player );
}

void QmlVlcPlayerProxy::componentComplete()
{
}

void QmlVlcPlayerProxy::classEnd()
{
    m_audio.classEnd();

    auto em =  player().eventManager();

    em.unregister( h_onPlaying, h_onStopped, h_onEncounteredError );

}

QmlVlcPlayerProxy::~QmlVlcPlayerProxy()
{
    classEnd();

    if( m_libvlc ) {
        QmlVlcConfig::instance().releaseLibvlcInstance( );
        m_libvlc = 0;
    }
}

void QmlVlcPlayerProxy::currentItemEndReached()
{

}

QString QmlVlcPlayerProxy::get_vlcVersion()
{
    return QString::fromLatin1( libvlc_get_version() );
}

void QmlVlcPlayerProxy::play( bool play )
{
    if( play )
        player().play();
    else
        player().stop();
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

QString QmlVlcPlayerProxy::get_mrl()
{
    if( player().media() != nullptr ) {
        std::string mrl = player().media()->mrl();
        return QString::fromUtf8( mrl.data(), mrl.size() );
    }
    else {
        return "";
    }

}

void QmlVlcPlayerProxy::set_mrl( const QString& mrl )
{
    VLC::MediaPlayer& p = player();

    auto media = VLC::Media( *m_libvlc, mrl.toUtf8().constData(), VLC::Media::FromLocation );

    p.setMedia( media );
}

bool QmlVlcPlayerProxy::get_playing()
{
    return playing;
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

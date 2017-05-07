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

#include "QmlVlcAudio.h"

QmlVlcAudio::QmlVlcAudio( )
    : m_player( nullptr )
{ }


void QmlVlcAudio::classBegin( const std::shared_ptr<VLC::MediaPlayer>& n_player )
{
    m_player = n_player;

    h_onMuted       = player().eventManager().onMuted(       [this](){      Q_EMIT muteChanged();   } );
    h_onAudioVolume = player().eventManager().onAudioVolume( [this](float){ Q_EMIT volumeChanged(); } );

    h_ESAdded = player().eventManager().onESAdded( [this](libvlc_track_type_t trackType, int id) {
            if( trackType == libvlc_track_audio )
            {
                audioTrackList.push_back(id);
                Q_EMIT audioTrackAdded();
             } });
}

void QmlVlcAudio::classEnd()
{
    auto em =  player().eventManager();

    em.unregister( h_onMuted, h_onAudioVolume, h_ESAdded  );
}


QmlVlcAudio::~QmlVlcAudio()
{ }

int QmlVlcAudio::get_audiotrack()
{
    if ( audioTrackList.size() > 0 )
    {
         return audioTrackList[0];
    }

    return -1;
}


unsigned QmlVlcAudio::get_trackCount()
{
    return  player().audioTrackCount();
}

bool QmlVlcAudio::get_mute()
{
    return  player().mute();
}

void QmlVlcAudio::set_mute( bool mute )
{
     if (mute && ( audioTrackList.size() > 0 ) )
     {
         player().setAudioTrack(-1);
     }
     else if( ( audioTrackList.size() > 0 ) )
     {
         player().setAudioTrack( audioTrackList[0] );
     }
}

void QmlVlcAudio::toggleMute()
{
     player().toggleMute();
}

unsigned int QmlVlcAudio::get_volume()
{
    return  player().volume();
}

void QmlVlcAudio::set_volume( unsigned int v )
{
    player().setVolume( v );
}

int QmlVlcAudio::get_track()
{
     return player().audioTrack();
}


void QmlVlcAudio::set_track( int idx )
{
    if( idx < 0 )
        return;

     player().setAudioTrack( idx );
}

QmlVlcAudio::Output QmlVlcAudio::get_channel()
{
    return static_cast<Output>(  player().channel() );
}

void QmlVlcAudio::set_channel( QmlVlcAudio::Output ch )
{
     player().setChannel( static_cast<int>( ch ) );
}

QString QmlVlcAudio::description( signed int trackID )
{
    QString track_name;

    std::vector<VLC::TrackDescription> trackList =  player().audioTrackDescription();


    for( std::vector<VLC::TrackDescription>::iterator it = trackList.begin() ; it != trackList.end(); ++it )
    {

        if( (*it).id() == trackID )
        {
            track_name = QString::fromStdString( (*it).name() );
            break;
        }
    }

    return track_name;
}

int64_t QmlVlcAudio::get_delay()
{
    return  player().audioDelay();
}

void QmlVlcAudio::set_delay( int64_t delay )
{
     player().setAudioDelay( delay );
}

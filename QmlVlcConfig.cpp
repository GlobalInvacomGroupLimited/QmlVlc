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

#include "QmlVlcConfig.h"

#if defined(__APPLE__)
#include "vlc-plugins-iPhone.h"
#elif defined(__ANDROID__)
#include "vlc-plugins-android.h"
#elif defined(__RASPBERRY_PI__)
#include "vlc-plugins-raspi.h"
#else
#include "vlc-plugins-linux.h"
#endif

#include <QVector>
#include <QStringList>
#include <QDebug>

QmlVlcConfigProxy::QmlVlcConfigProxy( QObject* parent ) : QObject(parent) {}

QmlVlcConfig& QmlVlcConfig::instance()
{
    static QmlVlcConfig instance;
    return instance;
}

QmlVlcConfig::QmlVlcConfig( QObject* parent )
    :  QObject(parent), _networkCacheTime( -1 ), _adjustFilter( false ), _marqueeFilter( false ),
      _logoFilter( false ), _fecLog( false ), _noVideoTitleShow( true ),
      _hardwareAcceleration( true ), _trustedEnvironment( false ),
      _libvlcCounter( 0 ), _libvlc( nullptr )
{
}

QmlVlcConfig::~QmlVlcConfig()
{
    Q_ASSERT( 0 == _libvlcCounter );
}

void QmlVlcConfig::setNetworkCacheTime( int time )
{
    _networkCacheTime = time;
}

void QmlVlcConfig::enableAdjustFilter( bool enable )
{
    _adjustFilter = enable;
}

void QmlVlcConfig::enableMarqueeFilter( bool enable )
{
    _marqueeFilter = enable;
}

void QmlVlcConfig::enableLogoFilter( bool enable )
{
    _logoFilter = enable;
}



void QmlVlcConfig::enableFecLog( bool enable )
{
    _fecLog = enable;
}

void QmlVlcConfig::enableNoVideoTitleShow( bool enable )
{
    _noVideoTitleShow = enable;
}

void QmlVlcConfig::enableHardwareAcceleration( bool enable )
{
    _hardwareAcceleration = enable;
}

void QmlVlcConfig::setTrustedEnvironment( bool trusted )
{
    _trustedEnvironment = trusted;
}

bool QmlVlcConfig::trustedEnvironment() const
{
    return _trustedEnvironment;
}

struct TrustedOption
{
    const char* name;
    const char* value; //if 0 = all values are acceptable
};

static const TrustedOption trustedOptions[] = {
    { ":rtsp-http-port", 0 },
    { ":avformat-format", "mxg" },
    { ":demux", "h264" },
    { ":h264-fps", 0 },
};

bool QmlVlcConfig::isOptionTrusted( const QString& opt ) const
{
    if( trustedEnvironment() )
        return true;

    QStringList name2val = opt.split( '=' );
    if( 2 != name2val.size() )
        return false;

    name2val[0] = name2val[0].trimmed();
    name2val[1] = name2val[1].trimmed();

    const unsigned tsz =
        sizeof( trustedOptions ) / sizeof( trustedOptions[0] );

    for( unsigned i = 0; i < tsz; ++i ) {
        const TrustedOption& to = trustedOptions[i];
        if( name2val[0] == to.name ) {
            if( 0 == to.value || name2val[1] == to.value )
                return true;
        }
    }

    return true;
}

bool QmlVlcConfig::createLibvlcInstance()
{
    Q_ASSERT( ( _libvlcCounter && _libvlc ) || ( !_libvlcCounter && !_libvlc ) );
    if( _libvlc ) {
        ++_libvlcCounter;
        return true;
    }

    QVector<const char*> opts;

    QByteArray networkCachingBuf;
    if( _networkCacheTime >= 0 ) {
        opts.push_back( "--network-caching" );
        networkCachingBuf = QString::number( _networkCacheTime ).toLatin1();
        opts.push_back( networkCachingBuf.constData() );
    }

    if( _adjustFilter )
        opts.push_back( "--video-filter=adjust" );

    QString subFilters;
    if( _marqueeFilter )
        subFilters = QStringLiteral( "marq" );

    if( _logoFilter ) {
        if( !subFilters.isEmpty() )
            subFilters += ':';
        subFilters += QStringLiteral( "logo" );
    }

    QByteArray subFiltersBuf;
    if( !subFilters.isEmpty() ) {
        subFilters = QStringLiteral( "--sub-filter=" ) + subFilters;
        subFiltersBuf = subFilters.toLatin1();
        opts.push_back( subFiltersBuf.constData() );
    }

#ifdef VLC_DEBUG
        opts.push_back( "-vvv" );
#endif

    if( _fecLog )
        opts.push_back( "--fec-logging" );
    else
        opts.push_back( "--no-fec-logging" );

    if( _noVideoTitleShow )
        opts.push_back( "--no-video-title-show" );

    if( _hardwareAcceleration ) {
        opts.push_back( "--avcodec-hw=any" );
        opts.push_back( "--codec=avcodec");
        opts.push_back( "--no-osd");
        opts.push_back( "--no-spu");
    }

#ifdef DISABLE_AV
        opts.push_back( "--novideo" );
        opts.push_back( "--noaudio" );
#endif

    _libvlc = new VLC::Instance(opts.size(), opts.data());

#ifdef VLC_DEBUG
    _libvlc->logSet(
                [this](int level, const libvlc_log_t* type, std::string message) {
                    (void) level;
                    (void) type;

                    qDebug() << message.c_str();
                } );
#endif

   if( _libvlc == nullptr ) {
        qCritical( "Couldn't create libvlc instance. Check vlc plugins dir." );
        return false;
    }

    _libvlcCounter = 1;

    return true;
}


VLC::Instance *QmlVlcConfig::getLibvlcInstance()
{
    //Q_ASSERT( ( _libvlcCounter && _libvlc ) || ( !_libvlcCounter && !_libvlc ) );
    createLibvlcInstance();

    return _libvlc;
}


bool QmlVlcConfig::releaseLibvlcInstance( )
{
    if( !_libvlcCounter ) {
        Q_ASSERT( false );
        return false;
    }

#ifdef VLC_DEBUG
    _libvlc->logUnset();
#endif
    if( !--_libvlcCounter ) {
        delete _libvlc;
        _libvlc = nullptr;
    }
    return true;
}

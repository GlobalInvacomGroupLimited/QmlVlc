
#include <QOpenGLContext>
#include <QtGui/QGuiApplication>
#include "QmlVlcOpenGlOutput.h"


QmlVlcOpenGlOutput::QmlVlcOpenGlOutput()
    : surface(nullptr),
      context(nullptr),
      firstFrame(true),
      resizeCb(nullptr),
      report_opaque(nullptr)
{
    mBuffers[0] = NULL;
    mBuffers[1] = NULL;
    mBuffers[2] = NULL;
}

QmlVlcOpenGlOutput::~QmlVlcOpenGlOutput()
{
    cleanup();
}

void QmlVlcOpenGlOutput::classBegin( const std::shared_ptr<VLC::MediaPlayer>& player )
{
    m_player = player;
}



void QmlVlcOpenGlOutput::init()
{
#if defined(__APPLE__) || defined (__ANDROID__) || defined(__RASPBERRY_PI__)
    libvlc_video_engine_t engine = libvlc_video_engine_gles2;
#else
    libvlc_video_engine_t engine = libvlc_video_engine_opengl;
#endif

    m_player->setVideoOutputCallbacks(engine,
                [this]( const libvlc_video_setup_device_cfg_t *cfg, libvlc_video_setup_device_info_t *out ) {
                    return setup( cfg, out );
                },
                [this]( ) {
                    return cleanup( );
                },
                [this]( report_size_change resizeCb, void *report_opaque ) {
                    return widowResize( resizeCb, report_opaque );
                },
                [this]( const libvlc_video_render_cfg_t *cfg, libvlc_video_output_cfg_t *render_cfg ) {
                    return resizeRenderTextures( cfg, render_cfg );
                },
                [this]( ) {
                    return swap( );
                },
                [this]( bool current ) {
                    return make_current( current );
                },
                [this]( const char* current ) {
                    return get_proc_address( current );
                },
                [this]( libvlc_video_metadata_type_t type, const void *metadata ) {
                    return frame_metadata(type, metadata );
                },
                [this]( size_t plane ) {
                    return output_select_plane( plane );
                });
}

/// return the texture to be displayed
QOpenGLFramebufferObject *QmlVlcOpenGlOutput::getVideoFrame()
{
    if( resizeCb != nullptr ) {
        resizeCb(report_opaque, 1920, 1080);
    }

    std::lock_guard<std::mutex> lock(m_text_lock);
    if ( m_updated ) {
        std::swap(m_idx_swap, m_idx_display);
        m_updated = false;
    }
    return mBuffers[m_idx_display];
}


/// This callback is called during initialisation.
bool QmlVlcOpenGlOutput::setup( const libvlc_video_setup_device_cfg_t *cfg, libvlc_video_setup_device_info_t *out )
{
    (void)cfg;
    (void)out;

    if (!QOpenGLContext::supportsThreadedOpenGL())
        return false;

    m_width = 0;
    m_height = 0;
    return true;
}



void QmlVlcOpenGlOutput::widowResize(report_size_change resizeCallback, void *reportOpaque )
{
    resizeCb = resizeCallback;
    report_opaque = reportOpaque;
}


/// this callback will create the surfaces and FBO used by VLC to perform its rendering
bool QmlVlcOpenGlOutput::resizeRenderTextures( const libvlc_video_render_cfg_t *cfg, libvlc_video_output_cfg_t *render_cfg )
{
    if (cfg->width != m_width || cfg->height != m_height)
        cleanup();

    mBuffers[0] = new QOpenGLFramebufferObject(cfg->width, cfg->height);
    mBuffers[1] = new QOpenGLFramebufferObject(cfg->width, cfg->height);
    mBuffers[2] = new QOpenGLFramebufferObject(cfg->width, cfg->height);

    m_width = cfg->width;
    m_height = cfg->height;

    mBuffers[m_idx_render]->bind();

    render_cfg->opengl_format = GL_RGBA;
    render_cfg->full_range = true;
    render_cfg->colorspace = libvlc_video_colorspace_BT709;
    render_cfg->primaries  = libvlc_video_primaries_BT709;
    render_cfg->transfer   = libvlc_video_transfer_func_SRGB;

    return true;
}




/// This callback is called to release the texture and FBO created in resize
void QmlVlcOpenGlOutput::cleanup( )
{
    if ( m_width == 0 && m_height == 0 )
        return;

    delete mBuffers[0];
    mBuffers[0] = NULL;
    delete mBuffers[1];
    mBuffers[1] = NULL;
    delete mBuffers[2];
    mBuffers[2] = NULL;
}


///This callback is called after VLC performs drawing calls
void QmlVlcOpenGlOutput::swap( )
{
    std::lock_guard<std::mutex> lock(m_text_lock);

    m_updated = true;
    std::swap(m_idx_swap, m_idx_render);
    mBuffers[m_idx_render]->bind();

    if(firstFrame) {
        firstFrame = false;

        // Get the production of FBO textures started..
        QMetaObject::invokeMethod(this, "renderNext", Qt::QueuedConnection);
    }
}


/// This callback is called to set the OpenGL context
bool QmlVlcOpenGlOutput::make_current( bool current )
{
    if (current)
    {
        context->makeCurrent(surface);
    }
    else
        context->doneCurrent();
    return true;
}


/// This callback is called by VLC to get OpenGL functions.
void* QmlVlcOpenGlOutput::get_proc_address( const char* current )
{
    QOpenGLContext *ctx = context;
    return reinterpret_cast<void*>(ctx->getProcAddress(current));
}


void QmlVlcOpenGlOutput::frame_metadata(libvlc_video_metadata_type_t type, const void *metadata)
{
    (void) type;
    (void) metadata;
}


bool QmlVlcOpenGlOutput::output_select_plane(size_t plane)
{
    (void) plane;
    return true;
}



void QmlVlcOpenGlOutput::renderNext()
{
    QSize m_size = QSize(400, 400);
    //context->makeCurrent(window());

    QOpenGLFramebufferObject *fbo = getVideoFrame();

    if(fbo != nullptr)
    {
        emit textureReady(fbo->texture(), m_size);
    }
}

void QmlVlcOpenGlOutput::startRender()
{
    // Get the production of FBO textures started..
    QMetaObject::invokeMethod(this, "renderNext", Qt::QueuedConnection);
}

void QmlVlcOpenGlOutput::shutDown()
{
    context->makeCurrent(surface);
    context->doneCurrent();
    delete context;

    // schedule this to be deleted only after we're done cleaning up
    surface->deleteLater();

    // Stop event processing, move the thread to GUI and make sure it is deleted.
    exit();
    moveToThread(QGuiApplication::instance()->thread());
}


//QOpenGLFramebufferObject * QtVLCWidget::render()
//{
//    return mVLC->getVideoFrame();
//}

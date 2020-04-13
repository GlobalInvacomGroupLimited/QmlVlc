#ifndef QMLVLCOPENGLOUTPUT_H
#define QMLVLCOPENGLOUTPUT_H

#include <QObject>
#include <QThread>
#include <QOpenGLFramebufferObject>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLContext>
#include <memory>

#ifndef Q_MOC_RUN
#include <libvlcpp/vlcpp/vlc.hpp>
#endif // Q_MOC_RUN

typedef void (*report_size_change)(void *report_opaque, unsigned width, unsigned height);


class QmlVlcOpenGlOutput: public QThread
{
    Q_OBJECT
public:
    explicit QmlVlcOpenGlOutput( );

    void classBegin( const std::shared_ptr<VLC::MediaPlayer>& player );
    void init();
    ~QmlVlcOpenGlOutput();

    /// return the texture to be displayed
    QOpenGLFramebufferObject *getVideoFrame();

    QOffscreenSurface *surface;
    QOpenGLContext *context;

public slots:
    void renderNext();

    void startRender();

    void shutDown();

signals:
    void frameReady();

signals:
    void textureReady(int id, const QSize &size);


private:
    virtual  void widowResize(report_size_change resizeCb, void *report_opaque);

    /// this callback will create the surfaces and FBO used by VLC to perform its rendering
    virtual  bool resizeRenderTextures(const libvlc_video_render_cfg_t *cfg, libvlc_video_output_cfg_t *render_cfg);

    // This callback is called during initialisation.
    virtual  bool setup(const libvlc_video_setup_device_cfg_t *cfg, libvlc_video_setup_device_info_t *out);

    // This callback is called to release the texture and FBO created in resize
    virtual  void cleanup();

    //This callback is called after VLC performs drawing calls
    virtual  void swap();

    // This callback is called to set the OpenGL context
    virtual  bool make_current(bool current);

    // This callback is called by VLC to get OpenGL functions.
    virtual void* get_proc_address(const char* current);

    virtual void frame_metadata(libvlc_video_metadata_type_t type, const void *metadata);

    virtual bool output_select_plane(size_t plane);

private:
    std::shared_ptr<VLC::MediaPlayer> m_player;

    //FBO data
    unsigned m_width = 0;
    unsigned m_height = 0;
    std::mutex m_text_lock;
    QOpenGLFramebufferObject *mBuffers[3];
    GLuint m_tex[3];
    GLuint m_fbo[3];
    size_t m_idx_render = 0;
    size_t m_idx_swap = 1;
    size_t m_idx_display = 2;
    bool m_updated = false;
    bool firstFrame = true;
    report_size_change resizeCb;
    void* report_opaque;
};


#endif // QMLVLCOPENGLOUTPUT_H

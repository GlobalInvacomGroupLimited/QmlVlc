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
    void init(QSize initSize);
    ~QmlVlcOpenGlOutput();

    void updateSize(QSize size);

    QOffscreenSurface *surface;
    QOpenGLContext *context;

public slots:
    /// signal the texture to be displayed
    void getVideoFrame();

    void resize();

    void startRender();

    void shutDown();

signals:
    void frameReady();

    void textureReady(int id, const QSize &size);

    void framesDisplayed();


private:
    virtual  void widowResizeCb(report_size_change resizeCb, void *report_opaque);

    /// this callback will create the surfaces and FBO used by VLC to perform its rendering
    virtual  bool resizeRenderTexturesCb(const libvlc_video_render_cfg_t *cfg, libvlc_video_output_cfg_t *render_cfg);

    // This callback is called during initialisation.
    virtual  bool setupCb(const libvlc_video_setup_device_cfg_t *cfg, libvlc_video_setup_device_info_t *out);

    // This callback is called to release the texture and FBO created in resize
    virtual  void cleanupCb();

    //This callback is called after VLC performs drawing calls
    virtual  void swapCb();

    // This callback is called to set the OpenGL context
    virtual  bool makeCurrentCb(bool current);

    // This callback is called by VLC to get OpenGL functions.
    virtual void* getProcAddressCb(const char* current);

    virtual void frameMetadataCb(libvlc_video_metadata_type_t type, const void *metadata);

    virtual bool outputSelectPlaneCb(size_t plane);

    void cleanup();

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

    QSize m_size;

    int frameCounter;
    bool emitframesDisplayed;
};

#endif // QMLVLCOPENGLOUTPUT_H

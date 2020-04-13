#include "QmlVlcTextureNode.h"

QmlVlcTextureNode::QmlVlcTextureNode(QQuickWindow *window)
    : m_id(0),
      m_size(0, 0),
      m_texture(nullptr),
      m_window(window)
{
    // Our texture node must have a texture, so use the default 0 texture.
     m_texture = m_window->createTextureFromId(0, QSize(1, 1));
     setTexture(m_texture);
     setFiltering(QSGTexture::Linear);
}

QmlVlcTextureNode::~QmlVlcTextureNode()
{
    delete m_texture;
}

void QmlVlcTextureNode::newTexture(int id, const QSize &size) {
    m_mutex.lock();
    m_id = id;
    m_size = size;
    m_mutex.unlock();

    // We cannot call QQuickWindow::update directly here, as this is only allowed
    // from the rendering thread or GUI thread.
    emit pendingNewTexture();
}


    // Before the scene graph starts to render, we update to the pending texture
void QmlVlcTextureNode::prepareNode() {
    m_window->resetOpenGLState();
    m_mutex.lock();
    int newId = m_id;
    QSize size = m_size;
    m_id = 0;
    m_mutex.unlock();
    if (newId) {
        delete m_texture;
        // note: include QQuickWindow::TextureHasAlphaChannel if the rendered content
        // has alpha.
        m_texture = m_window->createTextureFromId(newId, size);
        setTexture(m_texture);

        markDirty(DirtyMaterial);

        // This will notify the rendering thread that the texture is now being rendered
        // and it can start rendering to the other one.
        emit textureInUse();
    }
}

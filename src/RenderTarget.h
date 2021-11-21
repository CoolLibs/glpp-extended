#pragma once

#include <glpp/Objects/Framebuffer.h>
#include <glpp/Objects/Texture.h>
#include "ImageSize.h"

namespace glpp {
namespace ext {

class RenderTarget {
public:
    const Texture& texture() const { return _texture; }

    /// Returns the RenderTarget that corresponds to the screen (i.e. OpenGL's default framebuffer)
    static const RenderTarget& screen();

    /// Binds this render target so that it will be the one that the following draw calls will render to
    /// It also calls glViewport to adapt it to the size of this framebuffer
    void      bind() const;
    void      resize(ImageSize size);
    ImageSize size() const;
    GLsizei   width() const { return size().width(); }
    GLsizei   height() const { return size().height(); }
    /// /!\ Changes the bound RenderTarget to be destination
    void blit_to(const RenderTarget& destination, Interpolation interpolation);
    /// /!\ Changes the bound RenderTarget to be dst_framebuffer_id
    void blit_to(GLuint dst_framebuffer_id, ImageSize dst_framebuffer_size, Interpolation interpolation);

private:
    Framebuffer _framebuffer;
    Texture     _texture;
};

} // namespace ext
} // namespace glpp
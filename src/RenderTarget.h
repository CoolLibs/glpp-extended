#pragma once

#include <glpp/glpp.hpp>
#include "ImageSize.h"
#include "Texture.h"

namespace glpp {

class RenderTarget {
public:
    explicit RenderTarget(ImageSize size);

    const Texture&           texture() const { return _texture; }
    const UniqueFramebuffer& framebuffer() const { return _framebuffer; }

    /// Binds this render target so that it will be the one that the following draw calls will render to
    /// It also calls glViewport to set the viewport to the size of this RenderTarget
    void      bind() const;
    void      resize(ImageSize size);
    ImageSize size() const;
    GLsizei   width() const { return size().width(); }
    GLsizei   height() const { return size().height(); }
    /// /!\ Changes the bound RenderTarget to be destination
    void blit_to(const RenderTarget& destination, Interpolation interpolation);
    /// /!\ Changes the bound RenderTarget to be dst_framebuffer_id
    void blit_to(GLuint dst_framebuffer_id, ImageSize dst_framebuffer_size, Interpolation interpolation);

    static GLuint screen_framebuffer_id() { return 0; }

private:
    UniqueFramebuffer _framebuffer;
    Texture           _texture;
};

} // namespace glpp
#include "RenderTarget.h"

namespace glpp {

RenderTarget::RenderTarget(ImageSize size)
{
    // const auto prev_fb = get_current_framebuffer();
    bind_framebuffer(_framebuffer);
    _texture.bind();
    _texture.resize(size);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *_texture, 0);
    check_errors();
    // bind_framebuffer(prev_fb);
}

void RenderTarget::bind() const
{
    bind_framebuffer(_framebuffer);
    viewport(0, 0, width(), height());
}

void RenderTarget::resize(ImageSize size)
{
    _texture.resize(size);
}

ImageSize RenderTarget::size() const
{
    return _texture.size();
}

void RenderTarget::blit_to(const RenderTarget& destination, Interpolation interpolation)
{
    blit_to(*destination._framebuffer, size(), interpolation);
}

void RenderTarget::blit_to(GLuint dst_framebuffer_id, ImageSize dst_framebuffer_size, Interpolation interpolation)
{
    bind_framebuffer_as_draw(dst_framebuffer_id);
    bind_framebuffer_as_read(_framebuffer);
    blit_framebuffer(0, 0, width(), height(),
                     0, 0, dst_framebuffer_size.width(), dst_framebuffer_size.height(),
                     GL_COLOR_BUFFER_BIT, interpolation);
    bind_framebuffer_as_read(dst_framebuffer_id); // Make sure that dst_framebuffer is bound also as read because we promise that it mimics bind()
}

} // namespace glpp
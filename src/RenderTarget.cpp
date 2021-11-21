#include "RenderTarget.h"

void RenderTarget::bind() const
{
    _framebuffer.bind();
    glViewport(0, 0, width(), height());
    check_errors();
}

void RenderTarget::blit_to(const RenderTarget& destination, Interpolation interpolation)
{
    blit_to(*destination._framebuffer, size(), interpolation);
}

void RenderTarget::blit_to(GLuint dst_framebuffer_id, ImageSize dst_framebuffer_size, Interpolation interpolation)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dst_framebuffer_id);
    check_errors();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, *_framebuffer);
    check_errors();
    glBlitFramebuffer(0, 0, width(), height(), 0, 0, dst_framebuffer_size.width(), dst_framebuffer_size.height(), GL_COLOR_BUFFER_BIT, raw(interpolation));
    check_errors();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, dst_framebuffer_id); // Make sure that dst_framebuffer is bound also as read because we promise that it mimics bind()
    check_errors();
}
#include "RenderTarget.h"

namespace glpp {

RenderTarget::RenderTarget(ImageSize size, const void* data, TextureLayout texture_layout)
    : _texture_layout{texture_layout}
{
    const auto prev_read_fb = get_current_read_framebuffer();
    const auto prev_draw_fb = get_current_draw_framebuffer();
    bind_framebuffer(_framebuffer);
    _texture.bind();
    _texture.upload_data(size, data, _texture_layout);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *_texture, 0);
    glpp_check_errors();
    bind_framebuffer_as_read(prev_read_fb);
    bind_framebuffer_as_draw(prev_draw_fb);
}

auto RenderTarget::get_current_bind_state() -> RenderTargetBindState
{
    RenderTargetBindState state{};
    glGetIntegerv(GL_VIEWPORT, state.viewport);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &state.read_framebuffer);
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &state.draw_framebuffer);
    return state;
}

void RenderTarget::restore_bind_state(const RenderTargetBindState& state)
{
    glViewport(state.viewport[0],
               state.viewport[1],
               state.viewport[2],
               state.viewport[3]);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, state.read_framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, state.draw_framebuffer);
}

void RenderTarget::bind() const
{
    bind_framebuffer(_framebuffer);
    viewport(0, 0, width(), height());
}

void RenderTarget::resize(ImageSize size)
{
    _texture.resize(size, texture_layout());
}

void RenderTarget::conservative_resize(ImageSize new_size)
{
    RenderTarget tmp{size(), nullptr, texture_layout()};
    blit_to(tmp, glpp::Interpolation::NearestNeighbour);
    resize(new_size);
    tmp.blit_to(*this, glpp::Interpolation::Linear);
}

ImageSize RenderTarget::size() const
{
    return _texture.size();
}

void RenderTarget::blit_to(const RenderTarget& destination, Interpolation interpolation)
{
    blit_to(*destination._framebuffer, destination.size(), interpolation);
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
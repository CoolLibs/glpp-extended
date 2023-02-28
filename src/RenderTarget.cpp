#include "RenderTarget.h"

namespace glpp {

void RenderTarget::create_depth_buffer(ImageSize size)
{
    _depth_buffer = DepthBuffer{size};
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depth_buffer->id());
    glpp_check_errors();
}

RenderTarget::RenderTarget(ImageSize size, const void* data, TextureLayout texture_layout, bool create_a_depth_buffer)
    : _texture_layout{texture_layout}
{
    with_bound_framebuffer([&]() {
        _texture.bind();
        _texture.upload_data(size, data, _texture_layout);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *_texture, 0);
        glpp_check_errors();

        if (create_a_depth_buffer)
            create_depth_buffer(size);
    });
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
    glBindFramebuffer(GL_READ_FRAMEBUFFER, static_cast<GLuint>(state.read_framebuffer));
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, static_cast<GLuint>(state.draw_framebuffer));
}

void RenderTarget::bind() const
{
    bind_framebuffer(_framebuffer);
    viewport(0, 0, width(), height());
}

void RenderTarget::resize(ImageSize size)
{
    _texture.resize(size, texture_layout());

    if (_depth_buffer)
    {
        with_bound_framebuffer([&]() {
            create_depth_buffer(size);
        });
    }
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

void RenderTarget::blit_to(const RenderTarget& destination, Interpolation interpolation, BlitTopLeftCorner position)
{
    blit_to(*destination._framebuffer, destination.size(), interpolation, position);
}

void RenderTarget::blit_to(GLuint dst_framebuffer_id, ImageSize dst_framebuffer_size, Interpolation interpolation, BlitTopLeftCorner position)
{
    bind_framebuffer_as_draw(dst_framebuffer_id);
    bind_framebuffer_as_read(_framebuffer);
    blit_framebuffer(0, 0, width(), height(),
                     position.x, position.y,
                     position.x + dst_framebuffer_size.width(), position.y + dst_framebuffer_size.height(),
                     GL_COLOR_BUFFER_BIT, interpolation);
    bind_framebuffer_as_read(dst_framebuffer_id); // Make sure that dst_framebuffer is bound also as read because we promise that it mimics bind()
}

} // namespace glpp
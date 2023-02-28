#pragma once

#include <glpp/glpp.hpp>
#include <optional>
#include "DepthBuffer.h"
#include "ImageSize.h"
#include "Texture2D.h"

namespace glpp {

struct RenderTargetBindState {
    GLint viewport[4];
    GLint read_framebuffer;
    GLint draw_framebuffer;

    RenderTargetBindState() = default;

    RenderTargetBindState(const RenderTargetBindState& other)
        : read_framebuffer{other.read_framebuffer}
        , draw_framebuffer{other.draw_framebuffer}
    {
        for (size_t i = 0; i < 4; ++i)
        {
            viewport[i] = other.viewport[i];
        }
    }
};

struct BlitTopLeftCorner {
    GLint x{0};
    GLint y{0};
};

class RenderTarget {
public:
    /// You can optionally upload some image data
    explicit RenderTarget(ImageSize     size,
                          const void*   data                  = nullptr,
                          TextureLayout texture_layout        = {},
                          bool          create_a_depth_buffer = false);

    const Texture2D&         texture() const { return _texture; }
    const UniqueFramebuffer& framebuffer() const { return _framebuffer; }

    static auto get_current_bind_state() -> RenderTargetBindState;
    static void restore_bind_state(const RenderTargetBindState&);

    /// Binds this render target so that it will be the one that the following draw calls will render to
    /// It also calls glViewport to set the viewport to the size of this RenderTarget
    void bind() const;
    /// Resizes the render target
    /// /!\ All of its content is lost. If you don't want that you can use conservative_resize() instead
    void resize(ImageSize size);
    /// Resizes the render target and preserves its content
    void      conservative_resize(ImageSize size);
    ImageSize size() const;
    GLsizei   width() const { return size().width(); }
    GLsizei   height() const { return size().height(); }
    /// /!\ Changes the bound RenderTarget to be destination
    void blit_to(const RenderTarget& destination, Interpolation interpolation, BlitTopLeftCorner position = {});
    /// /!\ Changes the bound RenderTarget to be dst_framebuffer_id
    void blit_to(GLuint dst_framebuffer_id, ImageSize dst_framebuffer_size, Interpolation interpolation, BlitTopLeftCorner position = {});

    static GLuint screen_framebuffer_id() { return 0; }

    TextureLayout texture_layout() const { return _texture_layout; }

    /// Binds the framebuffer, calls the callback, and then unbinds the framebuffer
    /// and restores the OpenGL state as it was before the call.
    template<typename Callable>
    void with_bound_framebuffer(Callable&& callback)
    {
        const auto prev_read_fb = get_current_read_framebuffer();
        const auto prev_draw_fb = get_current_draw_framebuffer();
        bind_framebuffer(_framebuffer);

        callback();

        bind_framebuffer_as_read(prev_read_fb);
        bind_framebuffer_as_draw(prev_draw_fb);
    }

private:
    void create_depth_buffer(ImageSize size);

private:
    UniqueFramebuffer          _framebuffer;
    Texture2D                  _texture;
    TextureLayout              _texture_layout;
    std::optional<DepthBuffer> _depth_buffer;
};

class RenderTargetBindState_RAII {
public:
    RenderTargetBindState_RAII()
        : _state{RenderTarget::get_current_bind_state()}
    {
    }

    ~RenderTargetBindState_RAII()
    {
        RenderTarget::restore_bind_state(_state);
    }

    RenderTargetBindState_RAII(const RenderTargetBindState_RAII&) = delete;
    RenderTargetBindState_RAII& operator=(const RenderTargetBindState_RAII&) = delete;

private:
    RenderTargetBindState _state;
};

} // namespace glpp
#include "Texture.h"

namespace glpp {

Texture::Texture(Interpolation minification_filter,
                 Interpolation magnification_filter,
                 Wrap          horizontal_wrap,
                 Wrap          vertical_wrap)
{
    bind_texture(_id);
    set_minification_filter(_id, minification_filter);
    set_magnification_filter(_id, magnification_filter);
    set_wrap_s(_id, horizontal_wrap);
    set_wrap_t(_id, vertical_wrap);
}

void Texture::bind() const
{
    bind_texture(_id);
}

void Texture::bind_to_texture_unit(GLenum slot_idx) const
{
    active_texture(slot_idx);
    bind();
}

void Texture::resize(ImageSize size, TextureLayout layout)
{
    upload_data(size, nullptr, layout);
}

void Texture::upload_data(ImageSize size, const void* data, TextureLayout layout)
{
    bind_texture(_id);
    texture_image_2D(*_id, layout.internal_format, size.width(), size.height(), layout.channels, layout.texel_data_type, data);
    _size = size;
}

} // namespace glpp
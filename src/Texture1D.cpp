#include "Texture1D.h"

namespace glpp {

Texture1D::Texture1D(Interpolation minification_filter,
                     Interpolation magnification_filter,
                     Wrap          wrap)
{
    bind_texture(_id);
    set_minification_filter(_id, minification_filter);
    set_magnification_filter(_id, magnification_filter);
    set_wrap_s(_id, wrap);
}

void Texture1D::bind() const
{
    bind_texture(_id);
}

void Texture1D::bind_to_texture_unit(GLenum slot_idx) const
{
    active_texture(slot_idx);
    bind();
}

void Texture1D::resize(GLsizei size, TextureLayout layout)
{
    upload_data(size, nullptr, layout);
}

void Texture1D::upload_data(GLsizei size, const void* data, TextureLayout layout)
{
    bind_texture(_id);
    texture_image_1D(*_id, layout.internal_format, size, layout.channels, layout.texel_data_type, data);
    _size = size;
}

} // namespace glpp
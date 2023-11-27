#include <glpp/Functions/Texture.h>

namespace glpp::internal {

template<typename UniqueTextureT, typename SizeType, void (*upload_data_impl)(GLuint, SizeType, const void*, TextureLayout)>
TextureBase<UniqueTextureT, SizeType, upload_data_impl>::TextureBase(
    Interpolation minification_filter,
    Interpolation magnification_filter
)
{
    bind_texture(_id);
    set_minification_filter(minification_filter);
    set_magnification_filter(magnification_filter);
}

template<typename UniqueTextureT, typename SizeType, void (*upload_data_impl)(GLuint, SizeType, const void*, TextureLayout)>
void TextureBase<UniqueTextureT, SizeType, upload_data_impl>::bind() const
{
    bind_texture(_id);
}

template<typename UniqueTextureT, typename SizeType, void (*upload_data_impl)(GLuint, SizeType, const void*, TextureLayout)>
void TextureBase<UniqueTextureT, SizeType, upload_data_impl>::bind_to_texture_unit(GLenum slot_idx) const
{
    active_texture(slot_idx);
    bind();
}

template<typename UniqueTextureT, typename SizeType, void (*upload_data_impl)(GLuint, SizeType, const void*, TextureLayout)>
void TextureBase<UniqueTextureT, SizeType, upload_data_impl>::resize(SizeType size, TextureLayout layout)
{
    upload_data(size, nullptr, layout);
}

template<typename UniqueTextureT, typename SizeType, void (*upload_data_impl)(GLuint, SizeType, const void*, TextureLayout)>
void TextureBase<UniqueTextureT, SizeType, upload_data_impl>::upload_data(SizeType size, const void* data, TextureLayout layout)
{
    bind_texture(_id);
    upload_data_impl(_id.id(), size, data, layout);
    _size = size;
}

template<typename UniqueTextureT, typename SizeType, void (*upload_data_impl)(GLuint, SizeType, const void*, TextureLayout)>
void TextureBase<UniqueTextureT, SizeType, upload_data_impl>::set_minification_filter(Interpolation interpolation)
{
    glpp::set_minification_filter(_id, interpolation);
}

template<typename UniqueTextureT, typename SizeType, void (*upload_data_impl)(GLuint, SizeType, const void*, TextureLayout)>
void TextureBase<UniqueTextureT, SizeType, upload_data_impl>::set_magnification_filter(Interpolation interpolation)
{
    glpp::set_magnification_filter(_id, interpolation);
}

template<typename UniqueTextureT, typename SizeType, void (*upload_data_impl)(GLuint, SizeType, const void*, TextureLayout)>
void TextureBase<UniqueTextureT, SizeType, upload_data_impl>::set_wrap(Wrap wrap)
{
    glpp::set_wrap(_id, wrap);
}

} // namespace glpp::internal

#pragma once

#include <glpp/glpp.hpp>
#include "ImageSize.h"

namespace glpp {

struct TextureLayout {
    InternalFormat internal_format = InternalFormat::RGBA;
    Channels       channels        = Channels::RGBA;
    TexelDataType  texel_data_type = TexelDataType::UnsignedByte;
};

class Texture {
public:
    explicit Texture(Interpolation minification_filter  = Interpolation::NearestNeighbour,
                     Interpolation magnification_filter = Interpolation::Linear,
                     Wrap          horizontal_wrap      = Wrap::Repeat,
                     Wrap          vertical_wrap        = Wrap::Repeat);

    void      bind() const;
    void      bind_to_texture_unit(GLenum slot_idx) const;
    ImageSize size() const { return _size; }
    void      resize(ImageSize size, TextureLayout layout = {});
    void      upload_data(ImageSize size, const void* data, TextureLayout layout = {});
    GLuint    operator*() const { return *_id; }

private:
    UniqueTexture _id;
    ImageSize     _size;
};

} // namespace glpp
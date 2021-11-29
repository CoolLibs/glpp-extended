#pragma once

#include <glpp/glpp.hpp>
#include "ImageSize.h"

namespace glpp {

class Texture {
public:
    Texture(Interpolation minification_filter  = Interpolation::NearestNeighbour,
            Interpolation magnification_filter = Interpolation::Linear,
            Wrap          horizontal_wrap      = Wrap::Repeat,
            Wrap          vertical_wrap        = Wrap::Repeat);

    void      bind() const;
    ImageSize size() const { return _size; }
    void      resize(ImageSize size);
    void      upload_data(ImageSize size, void* data);
    GLuint    operator*() const { return *_id; }

private:
    UniqueTexture _id;
    ImageSize     _size;
};

} // namespace glpp
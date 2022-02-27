#pragma once

#include <glpp/glpp.hpp>
#include "TextureLayout.h"

namespace glpp {

class Texture1D {
public:
    explicit Texture1D(Interpolation minification_filter  = Interpolation::NearestNeighbour,
                       Interpolation magnification_filter = Interpolation::Linear,
                       Wrap          wrap                 = Wrap::Repeat);

    void    bind() const;
    void    bind_to_texture_unit(GLenum slot_idx) const;
    GLsizei size() const { return _size; }
    void    resize(GLsizei size, TextureLayout layout = {});
    void    upload_data(GLsizei size, const void* data, TextureLayout layout = {});
    GLuint  operator*() const { return *_id; }

private:
    UniqueTexture1D _id;
    GLsizei         _size = 1;
};

} // namespace glpp
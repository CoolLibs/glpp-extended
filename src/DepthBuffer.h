#pragma once

#include "ImageSize.h"
#include "glpp/glpp.hpp"

namespace glpp {

class DepthBuffer {
public:
    explicit DepthBuffer(ImageSize size);

    auto id() const -> GLuint { return _id.id(); }

private:
    UniqueRenderbuffer _id{};
};

} // namespace glpp

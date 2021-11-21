#pragma once

#include <cassert>

namespace glpp {
namespace ext {

/// Represents the width and height of an axis-aligned rectangle. width() and height() are guaranteed to be >= 1
class ImageSize {
public:
    ImageSize() = default;
    ImageSize(GLsizei w, GLsizei h)
        : _width{w}, _height{h}
    {
        assert(w >= 1 && h >= 1);
    }
    friend bool operator==(const GLsizei&, const GLsizei&) = default;

    GLsizei width() const { return _width; }
    GLsizei height() const { return _height; }

    /// Sets the width. It must be >= 1
    void set_width(GLsizei w)
    {
        assert(w >= 1);
        _width = w;
    }

    /// Sets the height. It must be >= 1
    void set_height(GLsizei h)
    {
        assert(h >= 1);
        _height = h;
    }

private:
    GLsizei _width;
    GLsizei _height;
};

} // namespace ext
} // namespace glpp
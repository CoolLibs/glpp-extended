#include "DepthBuffer.h"

namespace glpp {

DepthBuffer::DepthBuffer(ImageSize size)
{
    glBindRenderbuffer(GL_RENDERBUFFER, *_id);
    glpp_check_errors();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.width(), size.height());
    glpp_check_errors();
}

} // namespace glpp
#pragma once

#include <glm/glm.hpp>
#include <glpp/glpp.hpp>
#include <string>
#include <utility>
#include <vector>

namespace glpp {
namespace ext {

/// Automatic uniform location handling: the first time a uniform is encountered its location is looked up, and then it is stored in a cache for next time
/// set() recognizes glm types and sets the uniform accordingly
class Program {
public:
    void attach_shader(GLuint shader_id) const { _program.attach_shader(shader_id); }
    void link() const { _program.link(); }

    /// You can call this function after `link()` to check if there was any errors during the linking.
    MaybeError check_linking_errors() const { return _program.check_linking_errors(); }
    /// This is a function to debug the state of your shader
    /// that you can call just before a draw call to make sure that uniforms have been properly set and a few other things.
    /// https://community.khronos.org/t/samplers-of-different-types-use-the-same-textur/66329/4
    MaybeError check_for_state_errors() const { return _program.check_for_state_errors(); }

    GLuint operator*() const { return *_program; }
    void   use() const { _program.use(); }
    void   set(const std::string& uniform_name, int v) const;
    void   set(const std::string& uniform_name, unsigned int v) const;
    void   set(const std::string& uniform_name, bool v) const;
    void   set(const std::string& uniform_name, float v) const;
    void   set(const std::string& uniform_name, const glm::vec2& v) const;
    void   set(const std::string& uniform_name, const glm::vec3& v) const;
    void   set(const std::string& uniform_name, const glm::vec4& v) const;
    void   set(const std::string& uniform_name, const glm::mat2& mat) const;
    void   set(const std::string& uniform_name, const glm::mat3& mat) const;
    void   set(const std::string& uniform_name, const glm::mat4& mat) const;

private:
    GLint uniform_location(const std::string& uniform_name) const;

private:
    glpp::Program                                      _program;
    mutable std::vector<std::pair<std::string, GLint>> _uniform_locations;
};

} // namespace ext
} // namespace glpp

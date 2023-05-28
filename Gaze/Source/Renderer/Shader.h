#ifndef GAZE_SHADER_H
#define GAZE_SHADER_H

#include <string>
#include <glm/gtc/type_ptr.hpp>

namespace Gaze {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        static Shader *Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    };

} // Gaze

#endif //GAZE_SHADER_H

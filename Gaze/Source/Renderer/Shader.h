#ifndef GAZE_SHADER_H
#define GAZE_SHADER_H

#include <string>

namespace Gaze {

    class Shader {
    public:
        Shader(const std::string &vertexSrc, const std::string &fragmentSrc);

        ~Shader();

        void Bind() const;

        void Unbind() const;

    private:
        uint32_t m_RendererID;
    };

} // Gaze

#endif //GAZE_SHADER_H

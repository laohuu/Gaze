#ifndef GAZE_ENGINE_OPENGLSHADER_H
#define GAZE_ENGINE_OPENGLSHADER_H

#include "Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Gaze {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);

        virtual ~OpenGLShader();

        void Bind() const override;

        void Unbind() const override;

        void SetInt(const std::string &name, int value) override;

        void SetIntArray(const std::string &name, int *values, uint32_t count) override;

        void SetFloat(const std::string &name, float value) override;

        void SetFloat2(const std::string &name, const glm::vec2 &value) override;

        void SetFloat3(const std::string &name, const glm::vec3 &value) override;

        void SetFloat4(const std::string &name, const glm::vec4 &value) override;

        void SetMat4(const std::string &name, const glm::mat4 &value) override;

        const std::string &GetName() const override { return m_Name; }

        void UploadUniformInt(const std::string &name, int value);

        void UploadUniformIntArray(const std::string &name, int *values, uint32_t count);

        void UploadUniformFloat(const std::string &name, float value);

        void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);

        void UploadUniformFloat3(const std::string &name, const glm::vec3 &value);

        void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

        void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);

        void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

    private:
        uint32_t m_RendererID;
        std::string m_Name;
    };
}


#endif //GAZE_ENGINE_OPENGLSHADER_H

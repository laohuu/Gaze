#ifndef GAZE_ENGINE_PARTICLESYSTEM_H
#define GAZE_ENGINE_PARTICLESYSTEM_H

#include <Gaze.h>
#include <glad/glad.h>


struct ParticleProps {
    glm::vec2 Position;
    glm::vec2 Velocity, VelocityVariation;
    glm::vec4 ColorBegin, ColorEnd;
    float SizeBegin, SizeEnd, SizeVariation;
    float LifeTime = 1.0f;
};

class ParticleSystem {
public:
    ParticleSystem(uint32_t maxParticles = 10000);

    void OnUpdate(Gaze::Timestep ts);

    void OnRender(Gaze::OrthographicCamera &camera);

    void Emit(const ParticleProps &particleProps);

private:
    struct Particle {
        glm::vec2 Position;
        glm::vec2 Velocity;
        glm::vec4 ColorBegin, ColorEnd;
        float Rotation = 0.0f;
        float SizeBegin, SizeEnd;

        float LifeTime = 1.0f;
        float LifeRemaining = 0.0f;

        bool Active = false;
    };
    std::vector<Particle> m_ParticlePool;
    uint32_t m_PoolIndex = 999;

    GLuint m_QuadVA = 0;
    std::unique_ptr<Gaze::Shader> m_ParticleShader;
    GLint m_ParticleShaderViewProj, m_ParticleShaderTransform, m_ParticleShaderColor;
};


#endif //GAZE_ENGINE_PARTICLESYSTEM_H

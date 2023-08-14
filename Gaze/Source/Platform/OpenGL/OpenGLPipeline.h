#ifndef GAZE_ENGINE_OPENGLPIPELINE_H
#define GAZE_ENGINE_OPENGLPIPELINE_H

#include "Renderer/Pipeline.h"

namespace Gaze
{
    class OpenGLPipeline : public Pipeline
    {
    public:
        OpenGLPipeline(const PipelineSpecification& spec);
        virtual ~OpenGLPipeline();

        virtual PipelineSpecification&       GetSpecification() { return m_Specification; }
        virtual const PipelineSpecification& GetSpecification() const { return m_Specification; }

        virtual void Invalidate() override;

        virtual void Bind() override;

    private:
        PipelineSpecification m_Specification;
        uint32_t              m_VertexArrayRendererID = 0;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_OPENGLPIPELINE_H

#ifndef GAZE_ENGINE_PIPELINE_H
#define GAZE_ENGINE_PIPELINE_H

#include "Core/Ref.h"

#include "Renderer/Buffer.h"
#include "Renderer/RenderPass.h"
#include "Renderer/Shader.h"

namespace Gaze
{
    struct PipelineSpecification
    {
        Ref<Shader>     Shader;
        BufferLayout    Layout;
        Ref<RenderPass> RenderPass;

        std::string DebugName;
    };

    class Pipeline : public RefCounted
    {
    public:
        virtual ~Pipeline() = default;

        virtual PipelineSpecification&       GetSpecification()       = 0;
        virtual const PipelineSpecification& GetSpecification() const = 0;

        virtual void Invalidate() = 0;

        // TEMP: remove this when render command buffers are a thing
        virtual void Bind() = 0;

        static Ref<Pipeline> Create(const PipelineSpecification& spec);
    };
} // namespace Gaze

#endif // GAZE_ENGINE_PIPELINE_H

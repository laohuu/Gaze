#ifndef GAZE_ENGINE_RENDERER_H
#define GAZE_ENGINE_RENDERER_H

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

#include "RenderCommandQueue.h"
#include "RenderPass.h"
#include "RendererContext.h"

#include "Core/Application.h"

#include "RendererCapabilities.h"

#include "Scene/Scene.h"

namespace Gaze
{
    class ShaderLibrary;

    struct RendererConfig
    {
        // "Experimental" features
        bool ComputeEnvironmentMaps = false;
    };

    class Renderer
    {
    public:
        typedef void (*RenderCommandFn)(void*);

        static Ref<RendererContext> GetContext() { return Application::Get().GetWindow().GetRenderContext(); }

        static void Init();
        static void Shutdown();

        static RendererCapabilities& GetCapabilities();

        static Ref<ShaderLibrary> GetShaderLibrary();

        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(OrthographicCamera& camera);

        static void EndScene();

        static void Submit(Ref<Shader>&                  shader,
                           const Gaze::Ref<VertexArray>& vertexArray,
                           const glm::mat4&              transform = glm::mat4(1.0f));

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> s_SceneData;
    };

    namespace Utils
    {
        inline void DumpGPUInfo()
        {
            auto& caps = Renderer::GetCapabilities();
            GZ_CORE_TRACE("GPU Info:");
            GZ_CORE_TRACE("  Vendor: {0}", caps.Vendor);
            GZ_CORE_TRACE("  Device: {0}", caps.Device);
            GZ_CORE_TRACE("  Version: {0}", caps.Version);
        }
    } // namespace Utils

} // namespace Gaze

#endif // GAZE_ENGINE_RENDERER_H

#ifndef GAZE_ENGINE_RENDERER2D_H
#define GAZE_ENGINE_RENDERER2D_H

#include "Camera.h"
#include "OrthographicCamera.h"
#include "Texture.h"

#include "Renderer/EditorCamera.h"
#include "Scene/Components.h"

namespace Gaze {

    class Renderer2D {
    public:
        static void Init();

        static void Shutdown();

        static void BeginScene(const OrthographicCamera &camera); // TODO: Remove
        static void BeginScene(const Camera &camera, const glm::mat4 &transform);

        static void BeginScene(const EditorCamera &camera);

        static void EndScene();

        static void Flush();

        // Primitives
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);

        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);

        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Gaze::Ref<Texture2D> &texture,
                             float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));

        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Gaze::Ref<Texture2D> &texture,
                             float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));

        static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, int entityID = -1);

        static void DrawQuad(const glm::mat4 &transform, const Gaze::Ref<Texture2D> &texture, float tilingFactor = 1.0f,
                             const glm::vec4 &tintColor = glm::vec4(1.0f), int entityID = -1);

        static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                    const glm::vec4 &color);

        static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                    const glm::vec4 &color);

        static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                    const Gaze::Ref<Texture2D> &texture, float tilingFactor = 1.0f,
                                    const glm::vec4 &tintColor = glm::vec4(1.0f));

        static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                    const Gaze::Ref<Texture2D> &texture, float tilingFactor = 1.0f,
                                    const glm::vec4 &tintColor = glm::vec4(1.0f));

        static void DrawSprite(const glm::mat4 &transform, SpriteRendererComponent &src, int entityID);

        // Stats
        struct Statistics {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() const { return QuadCount * 4; }

            uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
        };

        static void ResetStats();

        static Statistics GetStats();

    private:
        static void StartBatch();

        static void NextBatch();
    };

} // Gaze

#endif //GAZE_ENGINE_RENDERER2D_H

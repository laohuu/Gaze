#ifndef GAZE_ENGINE_RENDERER2D_H
#define GAZE_ENGINE_RENDERER2D_H

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Gaze {

    class Renderer2D {
    public:
        static void Init();

        static void Shutdown();

        static void BeginScene(const OrthographicCamera &camera);

        static void EndScene();

        static void Flush();

        // Primitives
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);

        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);

        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Gaze::Ref<Texture2D> &texture,
                             float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));

        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Gaze::Ref<Texture2D> &texture,
                             float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));


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
    };

} // Gaze

#endif //GAZE_ENGINE_RENDERER2D_H

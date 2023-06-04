#ifndef GAZE_ENGINE_SCENESERIALIZER_H
#define GAZE_ENGINE_SCENESERIALIZER_H

#include "Scene.h"

namespace Gaze {

    class SceneSerializer {
    public:
        SceneSerializer(const Gaze::Ref<Scene> &scene);

        void Serialize(const std::string &filepath); //yaml

        void SerializeRuntime(const std::string &filepath); //Binary

        bool Deserialize(const std::string &filepath);

        bool DeserializeRuntime(const std::string &filepath);

    private:
        Gaze::Ref<Scene> m_Scene;
    };

} // Gaze

#endif //GAZE_ENGINE_SCENESERIALIZER_H

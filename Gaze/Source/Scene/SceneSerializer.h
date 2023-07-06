#ifndef GAZE_ENGINE_SCENESERIALIZER_H
#define GAZE_ENGINE_SCENESERIALIZER_H

#include "Scene.h"

namespace YAML
{
    class Emitter;
    class Node;
} // namespace YAML

namespace Gaze
{

    class SceneSerializer
    {
    public:
        SceneSerializer(const Ref<Scene>& scene);

        void Serialize(const std::filesystem::path& filepath);
        void SerializeToYAML(YAML::Emitter& out);
        void SerializeRuntime(const std::filesystem::path& filepath);

        bool Deserialize(const std::filesystem::path& filepath);
        bool DeserializeFromYAML(const std::string& yamlString);
        bool DeserializeRuntime(const std::filesystem::path& filepath);

    public:
        static void SerializeEntity(YAML::Emitter& out, Entity entity);
        static void DeserializeEntities(YAML::Node& entitiesNode, Ref<Scene> scene);

    private:
        Gaze::Ref<Scene> m_Scene;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_SCENESERIALIZER_H

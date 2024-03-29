#include "SceneSerializer.h"
#include "GazePCH.h"

#include "Components.h"
#include "Core/UUID.h"
#include "Entity.h"
#include "Project/Project.h"
#include "Scripting/ScriptEngine.h"
#include "Utilities/YAMLSerializationHelpers.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

namespace Gaze
{
    SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : m_Scene(scene) {}

    void SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity)
    {
        UUID uuid = entity.GetComponent<IDComponent>().ID;
        out << YAML::BeginMap; // Entity
        out << YAML::Key << "Entity";
        out << YAML::Value << uuid;

        if (entity.HasComponent<TagComponent>())
        {
            out << YAML::Key << "TagComponent";
            out << YAML::BeginMap; // TagComponent

            auto& tag = entity.GetComponent<TagComponent>().Tag;
            out << YAML::Key << "Tag" << YAML::Value << tag;

            out << YAML::EndMap; // TagComponent
        }

        if (entity.HasComponent<TransformComponent>())
        {
            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap; // TransformComponent

            auto& transform = entity.GetComponent<TransformComponent>();
            out << YAML::Key << "Position" << YAML::Value << transform.Translation;
            out << YAML::Key << "Rotation" << YAML::Value << transform.RotationEuler;
            out << YAML::Key << "Scale" << YAML::Value << transform.Scale;

            out << YAML::EndMap; // TransformComponent
        }

        if (entity.HasComponent<CameraComponent>())
        {
            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap; // CameraComponent

            auto& cameraComponent = entity.GetComponent<CameraComponent>();
            auto& camera          = cameraComponent.Camera;

            out << YAML::Key << "Camera" << YAML::Value;
            out << YAML::BeginMap; // Camera
            out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
            out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
            out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
            out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
            out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
            out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
            out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
            out << YAML::EndMap; // Camera

            out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
            out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;

            out << YAML::EndMap; // CameraComponent
        }

        if (entity.HasComponent<ScriptComponent>())
        {
            auto& scriptComponent = entity.GetComponent<ScriptComponent>();

            out << YAML::Key << "ScriptComponent";
            out << YAML::BeginMap; // ScriptComponent
            out << YAML::Key << "ClassName" << YAML::Value << scriptComponent.ClassName;

            // Fields
            Ref<ScriptClass> entityClass = ScriptEngine::GetEntityClass(scriptComponent.ClassName);
            const auto&      fields      = entityClass->GetFields();
            if (fields.size() > 0)
            {
                out << YAML::Key << "ScriptFields" << YAML::Value;
                auto& entityFields = ScriptEngine::GetScriptFieldMap(entity);
                out << YAML::BeginSeq;
                for (const auto& [name, field] : fields)
                {
                    if (entityFields.find(name) == entityFields.end())
                        continue;

                    out << YAML::BeginMap; // ScriptField
                    out << YAML::Key << "Name" << YAML::Value << name;
                    out << YAML::Key << "Type" << YAML::Value << Utils::ScriptFieldTypeToString(field.Type);

                    out << YAML::Key << "Data" << YAML::Value;
                    ScriptFieldInstance& scriptField = entityFields.at(name);

                    switch (field.Type)
                    {
                        WRITE_SCRIPT_FIELD(Float, float);
                        WRITE_SCRIPT_FIELD(Double, double);
                        WRITE_SCRIPT_FIELD(Bool, bool);
                        WRITE_SCRIPT_FIELD(Char, char);
                        WRITE_SCRIPT_FIELD(Byte, int8_t);
                        WRITE_SCRIPT_FIELD(Short, int16_t);
                        WRITE_SCRIPT_FIELD(Int, int32_t);
                        WRITE_SCRIPT_FIELD(Long, int64_t);
                        WRITE_SCRIPT_FIELD(UByte, uint8_t);
                        WRITE_SCRIPT_FIELD(UShort, uint16_t);
                        WRITE_SCRIPT_FIELD(UInt, uint32_t);
                        WRITE_SCRIPT_FIELD(ULong, uint64_t);
                        WRITE_SCRIPT_FIELD(Vector2, glm::vec2);
                        WRITE_SCRIPT_FIELD(Vector3, glm::vec3);
                        WRITE_SCRIPT_FIELD(Vector4, glm::vec4);
                        WRITE_SCRIPT_FIELD(Entity, UUID);
                    }
                    out << YAML::EndMap; // ScriptFields
                }
                out << YAML::EndSeq;
            }

            out << YAML::EndMap; // ScriptComponent
        }

        if (entity.HasComponent<SpriteRendererComponent>())
        {
            out << YAML::Key << "SpriteRendererComponent";
            out << YAML::BeginMap; // SpriteRendererComponent

            auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();
            out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;
            if (spriteRendererComponent.Texture)
                out << YAML::Key << "TexturePath" << YAML::Value << spriteRendererComponent.Texture->GetPath();

            out << YAML::Key << "TilingFactor" << YAML::Value << spriteRendererComponent.TilingFactor;

            out << YAML::EndMap; // SpriteRendererComponent
        }

        if (entity.HasComponent<CircleRendererComponent>())
        {
            out << YAML::Key << "CircleRendererComponent";
            out << YAML::BeginMap; // CircleRendererComponent

            auto& circleRendererComponent = entity.GetComponent<CircleRendererComponent>();
            out << YAML::Key << "Color" << YAML::Value << circleRendererComponent.Color;
            out << YAML::Key << "Thickness" << YAML::Value << circleRendererComponent.Thickness;
            out << YAML::Key << "Fade" << YAML::Value << circleRendererComponent.Fade;

            out << YAML::EndMap; // CircleRendererComponent
        }

        if (entity.HasComponent<RigidBody2DComponent>())
        {
            out << YAML::Key << "RigidBody2DComponent";
            out << YAML::BeginMap; // RigidBody2DComponent

            auto& rb2dComponent = entity.GetComponent<RigidBody2DComponent>();
            out << YAML::Key << "BodyType" << YAML::Value << RigidBody2DBodyTypeToString(rb2dComponent.Type);
            out << YAML::Key << "FixedRotation" << YAML::Value << rb2dComponent.FixedRotation;

            out << YAML::EndMap; // RigidBody2DComponent
        }

        if (entity.HasComponent<BoxCollider2DComponent>())
        {
            out << YAML::Key << "BoxCollider2DComponent";
            out << YAML::BeginMap; // BoxCollider2DComponent

            auto& bc2dComponent = entity.GetComponent<BoxCollider2DComponent>();
            out << YAML::Key << "Offset" << YAML::Value << bc2dComponent.Offset;
            out << YAML::Key << "Size" << YAML::Value << bc2dComponent.Size;
            out << YAML::Key << "Density" << YAML::Value << bc2dComponent.Density;
            out << YAML::Key << "Friction" << YAML::Value << bc2dComponent.Friction;
            out << YAML::Key << "Restitution" << YAML::Value << bc2dComponent.Restitution;
            out << YAML::Key << "RestitutionThreshold" << YAML::Value << bc2dComponent.RestitutionThreshold;

            out << YAML::EndMap; // BoxCollider2DComponent
        }

        if (entity.HasComponent<CircleCollider2DComponent>())
        {
            out << YAML::Key << "CircleCollider2DComponent";
            out << YAML::BeginMap; // CircleCollider2DComponent

            auto& cc2dComponent = entity.GetComponent<CircleCollider2DComponent>();
            out << YAML::Key << "Offset" << YAML::Value << cc2dComponent.Offset;
            out << YAML::Key << "Radius" << YAML::Value << cc2dComponent.Radius;
            out << YAML::Key << "Density" << YAML::Value << cc2dComponent.Density;
            out << YAML::Key << "Friction" << YAML::Value << cc2dComponent.Friction;
            out << YAML::Key << "Restitution" << YAML::Value << cc2dComponent.Restitution;
            out << YAML::Key << "RestitutionThreshold" << YAML::Value << cc2dComponent.RestitutionThreshold;

            out << YAML::EndMap; // CircleCollider2DComponent
        }

        if (entity.HasComponent<RigidBodyComponent>())
        {
            out << YAML::Key << "RigidBodyComponent";
            out << YAML::BeginMap; // RigidBodyComponent

            auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();
            out << YAML::Key << "BodyType" << YAML::Value << (int)rigidBodyComponent.BodyType;
            out << YAML::Key << "Mass" << YAML::Value << rigidBodyComponent.Mass;
            out << YAML::Key << "LinearDrag" << YAML::Value << rigidBodyComponent.LinearDrag;
            out << YAML::Key << "AngularDrag" << YAML::Value << rigidBodyComponent.AngularDrag;
            out << YAML::Key << "DisableGravity" << YAML::Value << rigidBodyComponent.DisableGravity;
            out << YAML::Key << "IsKinematic" << YAML::Value << rigidBodyComponent.IsKinematic;
            out << YAML::Key << "CollisionDetection" << YAML::Value << (uint32_t)rigidBodyComponent.CollisionDetection;
            out << YAML::Key << "LockFlags" << YAML::Value << rigidBodyComponent.LockFlags;

            out << YAML::EndMap; // RigidBodyComponent
        }

        if (entity.HasComponent<PhysicsMaterialComponent>())
        {
            out << YAML::Key << "PhysicsMaterialComponent";
            out << YAML::BeginMap; // PhysicsMaterialComponent

            auto& physicsMaterial = entity.GetComponent<PhysicsMaterialComponent>();
            out << YAML::Key << "StaticFriction" << YAML::Value << physicsMaterial.StaticFriction;
            out << YAML::Key << "DynamicFriction" << YAML::Value << physicsMaterial.DynamicFriction;
            out << YAML::Key << "Bounciness" << YAML::Value << physicsMaterial.Bounciness;

            out << YAML::EndMap;
        }

        if (entity.HasComponent<BoxColliderComponent>())
        {
            out << YAML::Key << "BoxColliderComponent";
            out << YAML::BeginMap; // BoxColliderComponent

            auto& boxColliderComponent = entity.GetComponent<BoxColliderComponent>();
            out << YAML::Key << "Offset" << YAML::Value << boxColliderComponent.Offset;
            out << YAML::Key << "HalfSize" << YAML::Value << boxColliderComponent.HalfSize;
            out << YAML::Key << "IsTrigger" << YAML::Value << boxColliderComponent.IsTrigger;

            out << YAML::EndMap; // BoxColliderComponent
        }

        if (entity.HasComponent<SphereColliderComponent>())
        {
            out << YAML::Key << "SphereColliderComponent";
            out << YAML::BeginMap; // SphereColliderComponent

            auto& sphereColliderComponent = entity.GetComponent<SphereColliderComponent>();
            out << YAML::Key << "Radius" << YAML::Value << sphereColliderComponent.Radius;
            out << YAML::Key << "IsTrigger" << YAML::Value << sphereColliderComponent.IsTrigger;
            out << YAML::Key << "Offset" << YAML::Value << sphereColliderComponent.Offset;

            out << YAML::EndMap; // SphereColliderComponent
        }

        if (entity.HasComponent<CapsuleColliderComponent>())
        {
            out << YAML::Key << "CapsuleColliderComponent";
            out << YAML::BeginMap; // CapsuleColliderComponent

            auto& capsuleColliderComponent = entity.GetComponent<CapsuleColliderComponent>();
            out << YAML::Key << "Radius" << YAML::Value << capsuleColliderComponent.Radius;
            out << YAML::Key << "Height" << YAML::Value << capsuleColliderComponent.Height;
            out << YAML::Key << "Offset" << YAML::Value << capsuleColliderComponent.Offset;
            out << YAML::Key << "IsTrigger" << YAML::Value << capsuleColliderComponent.IsTrigger;

            out << YAML::EndMap; // CapsuleColliderComponent
        }

        if (entity.HasComponent<TextComponent>())
        {
            out << YAML::Key << "TextComponent";
            out << YAML::BeginMap; // TextComponent

            auto& textComponent = entity.GetComponent<TextComponent>();
            out << YAML::Key << "TextString" << YAML::Value << textComponent.TextString;
            // TODO: textComponent.FontAsset
            out << YAML::Key << "Color" << YAML::Value << textComponent.Color;
            out << YAML::Key << "Kerning" << YAML::Value << textComponent.Kerning;
            out << YAML::Key << "LineSpacing" << YAML::Value << textComponent.LineSpacing;

            out << YAML::EndMap; // TextComponent
        }

        out << YAML::EndMap; // Entity
    }

    void SceneSerializer::Serialize(const std::filesystem::path& filepath)
    {
        YAML::Emitter out;
        SerializeToYAML(out);

        std::ofstream fout(filepath);
        fout << out.c_str();
    }
    void SceneSerializer::SerializeToYAML(YAML::Emitter& out)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Scene";
        out << YAML::Value << m_Scene->GetName();
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

        // Sort entities by UUID (for better serializing)
        std::map<UUID, entt::entity> sortedEntityMap;
        auto                         idComponentView = m_Scene->m_Registry.view<IDComponent>();
        for (auto entity : idComponentView)
            sortedEntityMap[idComponentView.get<IDComponent>(entity).ID] = entity;

        // Serialize sorted entities
        for (auto [id, entity] : sortedEntityMap)
            SerializeEntity(out, {entity, m_Scene.Raw()});

        out << YAML::EndSeq;
        out << YAML::EndMap;
    }

    void SceneSerializer::SerializeRuntime(const std::filesystem::path& filepath)
    {
        // Not implemented
        GZ_CORE_ASSERT(false);
    }

    bool SceneSerializer::Deserialize(const std::filesystem::path& filepath)
    {
        std::ifstream stream(filepath);
        GZ_CORE_ASSERT(stream);
        std::stringstream strStream;
        strStream << stream.rdbuf();

        DeserializeFromYAML(strStream.str());

        return true;
    }

    bool SceneSerializer::DeserializeFromYAML(const std::string& yamlString)
    {
        YAML::Node data = YAML::Load(yamlString);
        if (!data["Scene"])
            return false;

        std::string sceneName = data["Scene"].as<std::string>();
        GZ_CORE_TRACE("Deserializing scene '{0}'", sceneName);

        auto entities = data["Entities"];
        if (entities)
            DeserializeEntities(entities, m_Scene);

        return true;
    }

    void SceneSerializer::DeserializeEntities(YAML::Node& entitiesNode, Ref<Scene> scene)
    {
        for (auto entity : entitiesNode)
        {
            uint64_t uuid = entity["Entity"].as<uint64_t>();

            std::string name;
            auto        tagComponent = entity["TagComponent"];
            if (tagComponent)
                name = tagComponent["Tag"].as<std::string>();

            GZ_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

            Entity deserializedEntity = scene->CreateEntityWithUUID(uuid, name);

            auto transformComponent = entity["TransformComponent"];
            if (transformComponent)
            {
                // Entities always have transforms
                auto& tc       = deserializedEntity.GetComponent<TransformComponent>();
                tc.Translation = transformComponent["Position"].as<glm::vec3>();
                tc.SetRotationEuler(transformComponent["Rotation"].as<glm::vec3>());
                tc.Scale = transformComponent["Scale"].as<glm::vec3>();
            }

            auto cameraComponent = entity["CameraComponent"];
            if (cameraComponent)
            {
                auto& cc = deserializedEntity.AddComponent<CameraComponent>();

                auto cameraProps = cameraComponent["Camera"];
                cc.Camera.SetProjectionType((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());

                cc.Camera.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
                cc.Camera.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
                cc.Camera.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

                cc.Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
                cc.Camera.SetOrthographicNearClip(cameraProps["OrthographicNear"].as<float>());
                cc.Camera.SetOrthographicFarClip(cameraProps["OrthographicFar"].as<float>());

                cc.Primary          = cameraComponent["Primary"].as<bool>();
                cc.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
            }

            auto scriptComponent = entity["ScriptComponent"];
            if (scriptComponent)
            {
                auto& sc          = deserializedEntity.AddComponent<ScriptComponent>();
                sc.ClassName      = scriptComponent["ClassName"].as<std::string>();
                auto scriptFields = scriptComponent["ScriptFields"];
                if (scriptFields)
                {
                    Ref<ScriptClass> entityClass = ScriptEngine::GetEntityClass(sc.ClassName);
                    GZ_CORE_ASSERT(entityClass);
                    const auto& fields       = entityClass->GetFields();
                    auto&       entityFields = ScriptEngine::GetScriptFieldMap(deserializedEntity);

                    for (auto scriptField : scriptFields)
                    {
                        std::string     name       = scriptField["Name"].as<std::string>();
                        std::string     typeString = scriptField["Type"].as<std::string>();
                        ScriptFieldType type       = Utils::ScriptFieldTypeFromString(typeString);

                        ScriptFieldInstance& fieldInstance = entityFields[name];

                        GZ_CORE_ASSERT(fields.find(name) != fields.end());

                        if (fields.find(name) == fields.end())
                            continue;

                        fieldInstance.Field = fields.at(name);

                        switch (type)
                        {
                            READ_SCRIPT_FIELD(Float, float);
                            READ_SCRIPT_FIELD(Double, double);
                            READ_SCRIPT_FIELD(Bool, bool);
                            READ_SCRIPT_FIELD(Char, char);
                            READ_SCRIPT_FIELD(Byte, int8_t);
                            READ_SCRIPT_FIELD(Short, int16_t);
                            READ_SCRIPT_FIELD(Int, int32_t);
                            READ_SCRIPT_FIELD(Long, int64_t);
                            READ_SCRIPT_FIELD(UByte, uint8_t);
                            READ_SCRIPT_FIELD(UShort, uint16_t);
                            READ_SCRIPT_FIELD(UInt, uint32_t);
                            READ_SCRIPT_FIELD(ULong, uint64_t);
                            READ_SCRIPT_FIELD(Vector2, glm::vec2);
                            READ_SCRIPT_FIELD(Vector3, glm::vec3);
                            READ_SCRIPT_FIELD(Vector4, glm::vec4);
                            READ_SCRIPT_FIELD(Entity, UUID);
                        }
                    }
                }
            }

            auto spriteRendererComponent = entity["SpriteRendererComponent"];
            if (spriteRendererComponent)
            {
                auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
                src.Color = spriteRendererComponent["Color"].as<glm::vec4>();

                if (spriteRendererComponent["TexturePath"])
                {
                    std::string texturePath = spriteRendererComponent["TexturePath"].as<std::string>();
                    auto        path        = Project::GetAssetFileSystemPath(texturePath);
                    src.Texture             = Texture2D::Create(path.string());
                }

                if (spriteRendererComponent["TilingFactor"])
                    src.TilingFactor = spriteRendererComponent["TilingFactor"].as<float>();
            }

            auto circleRendererComponent = entity["CircleRendererComponent"];
            if (circleRendererComponent)
            {
                auto& crc     = deserializedEntity.AddComponent<CircleRendererComponent>();
                crc.Color     = circleRendererComponent["Color"].as<glm::vec4>();
                crc.Thickness = circleRendererComponent["Thickness"].as<float>();
                crc.Fade      = circleRendererComponent["Fade"].as<float>();
            }

            auto rigidBody2DComponent = entity["RigidBody2DComponent"];
            if (rigidBody2DComponent)
            {
                auto& rb2d         = deserializedEntity.AddComponent<RigidBody2DComponent>();
                rb2d.Type          = RigidBody2DBodyTypeFromString(rigidBody2DComponent["BodyType"].as<std::string>());
                rb2d.FixedRotation = rigidBody2DComponent["FixedRotation"].as<bool>();
            }

            auto boxCollider2DComponent = entity["BoxCollider2DComponent"];
            if (boxCollider2DComponent)
            {
                auto& bc2d                = deserializedEntity.AddComponent<BoxCollider2DComponent>();
                bc2d.Offset               = boxCollider2DComponent["Offset"].as<glm::vec2>();
                bc2d.Size                 = boxCollider2DComponent["Size"].as<glm::vec2>();
                bc2d.Density              = boxCollider2DComponent["Density"].as<float>();
                bc2d.Friction             = boxCollider2DComponent["Friction"].as<float>();
                bc2d.Restitution          = boxCollider2DComponent["Restitution"].as<float>();
                bc2d.RestitutionThreshold = boxCollider2DComponent["RestitutionThreshold"].as<float>();
            }

            auto circleCollider2DComponent = entity["CircleCollider2DComponent"];
            if (circleCollider2DComponent)
            {
                auto& cc2d                = deserializedEntity.AddComponent<CircleCollider2DComponent>();
                cc2d.Offset               = circleCollider2DComponent["Offset"].as<glm::vec2>();
                cc2d.Radius               = circleCollider2DComponent["Radius"].as<float>();
                cc2d.Density              = circleCollider2DComponent["Density"].as<float>();
                cc2d.Friction             = circleCollider2DComponent["Friction"].as<float>();
                cc2d.Restitution          = circleCollider2DComponent["Restitution"].as<float>();
                cc2d.RestitutionThreshold = circleCollider2DComponent["RestitutionThreshold"].as<float>();
            }

            auto rigidBodyComponent = entity["RigidBodyComponent"];
            if (rigidBodyComponent)
            {
                auto& component          = deserializedEntity.AddComponent<RigidBodyComponent>();
                component.BodyType       = (RigidBodyComponent::Type)rigidBodyComponent["BodyType"].as<int>(0);
                component.Mass           = rigidBodyComponent["Mass"].as<float>(1.0f);
                component.LinearDrag     = rigidBodyComponent["LinearDrag"].as<float>(0.0f);
                component.AngularDrag    = rigidBodyComponent["AngularDrag"].as<float>(0.05f);
                component.DisableGravity = rigidBodyComponent["DisableGravity"].as<bool>(false);
                component.IsKinematic    = rigidBodyComponent["IsKinematic"].as<bool>(false);

                component.CollisionDetection =
                    (CollisionDetectionType)rigidBodyComponent["CollisionDetection"].as<uint32_t>(0);

                auto lockFlagsNode = rigidBodyComponent["LockFlags"];
                if (lockFlagsNode)
                {
                    component.LockFlags = lockFlagsNode.as<uint8_t>(0);
                }
                else
                {
                    component.LockFlags |= rigidBodyComponent["Constraints"]["LockPositionX"].as<bool>(false) ?
                                               (uint8_t)ActorLockFlag::TranslationX :
                                               0;
                    component.LockFlags |= rigidBodyComponent["Constraints"]["LockPositionY"].as<bool>(false) ?
                                               (uint8_t)ActorLockFlag::TranslationY :
                                               0;
                    component.LockFlags |= rigidBodyComponent["Constraints"]["LockPositionZ"].as<bool>(false) ?
                                               (uint8_t)ActorLockFlag::TranslationZ :
                                               0;
                    component.LockFlags |= rigidBodyComponent["Constraints"]["LockRotationX"].as<bool>(false) ?
                                               (uint8_t)ActorLockFlag::RotationX :
                                               0;
                    component.LockFlags |= rigidBodyComponent["Constraints"]["LockRotationY"].as<bool>(false) ?
                                               (uint8_t)ActorLockFlag::RotationY :
                                               0;
                    component.LockFlags |= rigidBodyComponent["Constraints"]["LockRotationZ"].as<bool>(false) ?
                                               (uint8_t)ActorLockFlag::RotationZ :
                                               0;
                }
            }

            auto physicsMaterialComponent = entity["PhysicsMaterialComponent"];
            if (physicsMaterialComponent)
            {
                auto& component           = deserializedEntity.AddComponent<PhysicsMaterialComponent>();
                component.StaticFriction  = physicsMaterialComponent["StaticFriction"].as<float>();
                component.DynamicFriction = physicsMaterialComponent["DynamicFriction"].as<float>();
                component.Bounciness      = physicsMaterialComponent["Bounciness"].as<float>();
            }

            auto boxColliderComponent = entity["BoxColliderComponent"];
            if (boxColliderComponent)
            {
                auto& component  = deserializedEntity.AddComponent<BoxColliderComponent>();
                component.Offset = boxColliderComponent["Offset"].as<glm::vec3>();
                if (boxColliderComponent["Size"])
                    component.HalfSize = boxColliderComponent["Size"].as<glm::vec3>() / 2.0f;
                else
                    component.HalfSize = boxColliderComponent["HalfSize"].as<glm::vec3>(glm::vec3(0.5f));
                component.IsTrigger = boxColliderComponent["IsTrigger"] && boxColliderComponent["IsTrigger"].as<bool>();
            }

            auto sphereColliderComponent = entity["SphereColliderComponent"];
            if (sphereColliderComponent)
            {
                auto& component  = deserializedEntity.AddComponent<SphereColliderComponent>();
                component.Radius = sphereColliderComponent["Radius"].as<float>();
                component.IsTrigger =
                    sphereColliderComponent["IsTrigger"] && sphereColliderComponent["IsTrigger"].as<bool>();
                component.Offset = sphereColliderComponent["Offset"].as<glm::vec3>(glm::vec3(0.0f));
            }

            auto capsuleColliderComponent = entity["CapsuleColliderComponent"];
            if (capsuleColliderComponent)
            {
                auto& component  = deserializedEntity.AddComponent<CapsuleColliderComponent>();
                component.Radius = capsuleColliderComponent["Radius"].as<float>();
                component.Height = capsuleColliderComponent["Height"].as<float>();
                component.Offset = capsuleColliderComponent["Offset"].as<glm::vec3>(glm::vec3 {0.0f, 0.0f, 0.0f});

                component.IsTrigger =
                    capsuleColliderComponent["IsTrigger"] && capsuleColliderComponent["IsTrigger"].as<bool>();
            }

            auto textComponent = entity["TextComponent"];
            if (textComponent)
            {
                auto& tc      = deserializedEntity.AddComponent<TextComponent>();
                tc.TextString = textComponent["TextString"].as<std::string>();
                // tc.FontAsset // TODO
                tc.Color       = textComponent["Color"].as<glm::vec4>();
                tc.Kerning     = textComponent["Kerning"].as<float>();
                tc.LineSpacing = textComponent["LineSpacing"].as<float>();
            }
        }
    }

    bool SceneSerializer::DeserializeRuntime(const std::filesystem::path& filepath)
    {
        // Not implemented
        GZ_CORE_ASSERT(false);
        return false;
    }

} // namespace Gaze
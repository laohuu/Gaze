#ifndef GAZE_ENGINE_YAMLSERIALIZATIONHELPERS_H
#define GAZE_ENGINE_YAMLSERIALIZATIONHELPERS_H

#include "Core/UUID.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <yaml-cpp/yaml.h>

namespace YAML
{
    template<>
    struct convert<glm::vec2>
    {
        static Node encode(const glm::vec2& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::vec2& rhs)
        {
            if (!node.IsSequence() || node.size() != 2)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

    template<>
    struct convert<glm::vec3>
    {
        static Node encode(const glm::vec3& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::vec3& rhs)
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<glm::vec4>
    {
        static Node encode(const glm::vec4& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::vec4& rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };

    template<>
    struct convert<Gaze::UUID>
    {
        static Node encode(const Gaze::UUID& uuid)
        {
            Node node;
            node.push_back((uint64_t)uuid);
            return node;
        }

        static bool decode(const Node& node, Gaze::UUID& uuid)
        {
            uuid = node.as<uint64_t>();
            return true;
        }
    };
} // namespace YAML

namespace Gaze
{
#define WRITE_SCRIPT_FIELD(FieldType, Type) \
    case ScriptFieldType::FieldType: \
        out << scriptField.GetValue<Type>(); \
        break

#define READ_SCRIPT_FIELD(FieldType, Type) \
    case ScriptFieldType::FieldType: { \
        Type value = scriptField["Data"].as<Type>(); \
        fieldInstance.SetValue(value); \
        break; \
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
        return out;
    }

    static std::string RigidBody2DBodyTypeToString(RigidBody2DComponent::BodyType bodyType)
    {
        switch (bodyType)
        {
            case RigidBody2DComponent::BodyType::Static:
                return "Static";
            case RigidBody2DComponent::BodyType::Dynamic:
                return "Dynamic";
            case RigidBody2DComponent::BodyType::Kinematic:
                return "Kinematic";
        }

        GZ_CORE_ASSERT(false, "Unknown body type");
        return {};
    }

    static RigidBody2DComponent::BodyType RigidBody2DBodyTypeFromString(const std::string& bodyTypeString)
    {
        if (bodyTypeString == "Static")
            return RigidBody2DComponent::BodyType::Static;
        if (bodyTypeString == "Dynamic")
            return RigidBody2DComponent::BodyType::Dynamic;
        if (bodyTypeString == "Kinematic")
            return RigidBody2DComponent::BodyType::Kinematic;

        GZ_CORE_ASSERT(false, "Unknown body type");
        return RigidBody2DComponent::BodyType::Static;
    }
} // namespace Gaze

#endif // GAZE_ENGINE_YAMLSERIALIZATIONHELPERS_H

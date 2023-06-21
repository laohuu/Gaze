#ifndef GAZE_ENGINE_PROJECT_H
#define GAZE_ENGINE_PROJECT_H

#include <filesystem>
#include <string>

#include "Core/Base.h"

namespace Gaze
{

    struct ProjectConfig
    {
        std::string Name = "Untitled";

        std::filesystem::path StartScene;

        std::filesystem::path AssetDirectory;
        std::filesystem::path ScriptModulePath;
    };

    class Project
    {
    public:
        static const std::filesystem::path& GetProjectDirectory()
        {
            GZ_CORE_ASSERT(s_ActiveProject);
            return s_ActiveProject->m_ProjectDirectory;
        }

        static std::filesystem::path GetAssetDirectory()
        {
            GZ_CORE_ASSERT(s_ActiveProject);
            return GetProjectDirectory() / s_ActiveProject->m_Config.AssetDirectory;
        }

        // TODO: move to asset manager when we have one
        static std::filesystem::path GetAssetFileSystemPath(const std::filesystem::path& path)
        {
            GZ_CORE_ASSERT(s_ActiveProject);
            return GetAssetDirectory() / path;
        }

        ProjectConfig& GetConfig() { return m_Config; }

        static Ref<Project> GetActive() { return s_ActiveProject; }

        static Ref<Project> New();
        static Ref<Project> Load(const std::filesystem::path& path);
        static bool         SaveActive(const std::filesystem::path& path);

    private:
        ProjectConfig         m_Config;
        std::filesystem::path m_ProjectDirectory;

        inline static Ref<Project> s_ActiveProject;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_PROJECT_H

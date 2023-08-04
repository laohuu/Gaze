#include "Project.h"
#include "GazePCH.h"

#include "ProjectSerializer.h"

namespace Gaze
{

    Ref<Project> Project::New()
    {
        s_ActiveProject = Ref<Project>::Create();
        return s_ActiveProject;
    }

    Ref<Project> Project::Load(const std::filesystem::path& path)
    {
        Ref<Project> project = Ref<Project>::Create();

        ProjectSerializer serializer(project);
        if (serializer.Deserialize(path))
        {
            project->m_ProjectDirectory = path.parent_path();
            s_ActiveProject             = project;
            return s_ActiveProject;
        }

        return nullptr;
    }

    bool Project::SaveActive(const std::filesystem::path& path)
    {
        ProjectSerializer serializer(s_ActiveProject);
        if (serializer.Serialize(path))
        {
            s_ActiveProject->m_ProjectDirectory = path.parent_path();
            return true;
        }

        return false;
    }

} // namespace Gaze
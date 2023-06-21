#ifndef GAZE_ENGINE_PROJECTSERIALIZER_H
#define GAZE_ENGINE_PROJECTSERIALIZER_H

#include "Project.h"

namespace Gaze
{

    class ProjectSerializer
    {
    public:
        ProjectSerializer(Ref<Project> project);

        bool Serialize(const std::filesystem::path& filepath);
        bool Deserialize(const std::filesystem::path& filepath);

    private:
        Ref<Project> m_Project;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_PROJECTSERIALIZER_H

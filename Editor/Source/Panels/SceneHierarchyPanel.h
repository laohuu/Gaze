#ifndef GAZE_ENGINE_SCENEHIERARCHYPANEL_H
#define GAZE_ENGINE_SCENEHIERARCHYPANEL_H

#include "Core/Base.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"

namespace Gaze {

    class SceneHierarchyPanel {
    public:
        SceneHierarchyPanel() = default;

        SceneHierarchyPanel(const Gaze::Ref<Scene> &scene);

        void SetContext(const Gaze::Ref<Scene> &scene);

        void OnImGuiRender();

    private:
        void DrawEntityNode(Entity entity);

    private:
        Gaze::Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };

} // Gaze

#endif //GAZE_ENGINE_SCENEHIERARCHYPANEL_H

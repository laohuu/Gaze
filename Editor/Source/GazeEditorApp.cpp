#include <Gaze.h>
#include <Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Gaze {
    class GazeEditorApp : public Application {
    public:
        GazeEditorApp(const ApplicationSpecification &spec)
                : Application(spec) {
            PushLayer(new EditorLayer());
        }

        ~GazeEditorApp() override = default;

    private:

    };

    Application *CreateApplication() {
        ApplicationSpecification spec;
        spec.Name = "GazeEditorApp";

        return new GazeEditorApp(spec);
    }
}

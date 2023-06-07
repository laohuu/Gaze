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

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        ApplicationSpecification spec;
        spec.Name = "EditorApp";
        spec.CommandLineArgs = args;

        return new GazeEditorApp(spec);
    }
}

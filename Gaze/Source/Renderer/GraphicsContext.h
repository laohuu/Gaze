#ifndef GAZE_GRAPHICSCONTEXT_H
#define GAZE_GRAPHICSCONTEXT_H
namespace Gaze {

    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;

        virtual void SwapBuffers() = 0;
    };

}
#endif //GAZE_GRAPHICSCONTEXT_H

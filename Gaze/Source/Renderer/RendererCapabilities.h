#ifndef GAZE_ENGINE_RENDERERCAPABILITIES_H
#define GAZE_ENGINE_RENDERERCAPABILITIES_H

#include <string>

namespace Gaze
{
    struct RendererCapabilities
    {
        std::string Vendor;
        std::string Device;
        std::string Version;

        int   MaxSamples      = 0;
        float MaxAnisotropy   = 0.0f;
        int   MaxTextureUnits = 0;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_RENDERERCAPABILITIES_H

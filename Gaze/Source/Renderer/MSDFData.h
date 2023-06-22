#ifndef GAZE_ENGINE_MSDFDATA_H
#define GAZE_ENGINE_MSDFDATA_H

#include <vector>

#undef INFINITE
#include <msdf-atlas-gen/msdf-atlas-gen.h>

namespace Gaze
{

    struct MSDFData
    {
        std::vector<msdf_atlas::GlyphGeometry> Glyphs;
        msdf_atlas::FontGeometry               FontGeometry;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_MSDFDATA_H

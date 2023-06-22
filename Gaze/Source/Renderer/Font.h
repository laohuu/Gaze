#ifndef GAZE_ENGINE_RENDERER_FONT_H
#define GAZE_ENGINE_RENDERER_FONT_H

#include <filesystem>

#include "Core/Base.h"
#include "Renderer/Texture.h"

namespace Gaze
{

    struct MSDFData;

    class Font
    {
    public:
        Font(const std::filesystem::path& font);
        ~Font();

        const MSDFData* GetMSDFData() const { return m_Data; }
        Ref<Texture2D>  GetAtlasTexture() const { return m_AtlasTexture; }

        static Ref<Font> GetDefault();

    private:
        MSDFData*      m_Data;
        Ref<Texture2D> m_AtlasTexture;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_RENDERER_FONT_H

#ifndef GAZE_ENGINE_CONTENTBROWSERPANEL_H
#define GAZE_ENGINE_CONTENTBROWSERPANEL_H

#include <filesystem>
#include "Renderer/Texture.h"

namespace Gaze {

    class ContentBrowserPanel {
    public:
        ContentBrowserPanel();

        void OnImGuiRender();

    private:
        std::filesystem::path m_BaseDirectory;
        std::filesystem::path m_CurrentDirectory;

        Ref<Texture2D> m_DirectoryIcon;
        Ref<Texture2D> m_FileIcon;
    };

} // Gaze

#endif //GAZE_ENGINE_CONTENTBROWSERPANEL_H

#ifndef GAZE_ENGINE_CONTENTBROWSERPANEL_H
#define GAZE_ENGINE_CONTENTBROWSERPANEL_H

#include <filesystem>

namespace Gaze {

    class ContentBrowserPanel {
    public:
        ContentBrowserPanel();

        void OnImGuiRender();

    private:
        std::filesystem::path m_CurrentDirectory;
    };

} // Gaze

#endif //GAZE_ENGINE_CONTENTBROWSERPANEL_H

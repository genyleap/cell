#if __has_include("html.hpp")
#   include "html.hpp"
#else
#   error "Cell's "html.hpp" was not found!"
#endif

#if __has_include("core.hpp")
#   include "core.hpp"
#else
#   error "Cell's "core.hpp" was not found!"
#endif

#include "filesystem.hpp"

CELL_NAMESPACE_BEGIN(Cell::System)

Html::Html()
{
}
Html::~Html()
{
}

std::vector<std::string> Html::getTags(const std::string_view content)
{
    if (Engine::self().isFilePath(content.data()))
    {
        FileSystem::FileManager fm;
        std::string html = fm.read(content.data());
        size_t start_pos = __cell_zero;
        while ((start_pos = html.find("<", start_pos)) != std::string::npos) {
            size_t end_pos = html.find(">", start_pos);
            if (end_pos != std::string::npos) {
                std::string tag = html.substr(start_pos, end_pos - start_pos + 1);
                m_tags.push_back(tag);
                start_pos = end_pos + 1;
            } else {
                break;
            }
        }
    } else {
        std::string html = content.data();
        size_t start_pos = __cell_zero;
        while ((start_pos = html.find("<", start_pos)) != std::string::npos) {
            size_t end_pos = html.find(">", start_pos);
            if (end_pos != std::string::npos) {
                std::string tag = html.substr(start_pos, end_pos - start_pos + 1);
                m_tags.push_back(tag);
                start_pos = end_pos + 1;
            } else {
                break;
            }
        }
    }
    return m_tags;
}

CELL_NAMESPACE_END

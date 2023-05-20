#if __has_include("xml.hpp")
#   include "xml.hpp"
#else
#   error "Cell's "xml.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

#if __has_include("core/filesystem.hpp")
#   include "core/filesystem.hpp"
#else
#   error "Cell's "core/filesystem.hpp" was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::FileSystem;
CELL_USING_NAMESPACE Cell::eLogger;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Settings)

XmlSetting::XmlSetting()
{
}


XmlSetting::~XmlSetting()
{
}

void XmlSetting::setValue(const std::string& section, const std::string& key, const std::string& value)
{
    xmlStructure.settingData[section][key] = value;
}

bool XmlSetting::getValue(const std::string& section, const std::string& key, std::string& value) const
{
    auto sectionIter = xmlStructure.settingData.find(section);
    if (sectionIter == xmlStructure.settingData.end()) {
        return false;
    }
    auto keyIter = sectionIter->second.find(key);
    if (keyIter == sectionIter->second.end())
    {
        return false;
    }
    value = keyIter->second;
    return true;
}

bool XmlSetting::save()
{
    auto fileIO = FileManager();
    auto file = fileIO.stream(xmlStructure.filename.value());
    if (file.is_open()) {
        Encoding encoding = Encoding::UTF8; // Set UTF-8
        file << "<?xml version=\"1.0\" encoding=\"" + encodingList.at(encoding) + "\" ?>" << std::endl;
        file << settingBegin << std::endl;
        for (const auto& [section, keys] : xmlStructure.settingData) {
            file << "  <" << section << ">" << std::endl;
            for (const auto& [key, value] : keys) {
                file << "    <" << key << ">" << value << "</" << key << ">" << std::endl;
            }
            for (const auto& comment : xmlStructure.comments[section]) {
                file << "    <!-- " << comment << " -->" << std::endl;
            }
            file << "  </" << section << ">" << std::endl;
        }
        file << settingEnd << std::endl;
        file.close();
        return true;
    }
    return false;
}

bool XmlSetting::read(const std::string& filename)
{
    xmlStructure.filename = filename;
    auto fileIO = FileManager();
    auto file = fileIO.get(filename);
    if (file.is_open()) {
        std::string line;
        std::string currentSection;
        while (std::getline(file, line)) {
            // Trim leading/trailing whitespace
            line = Engine::trim(line);
            if (line.empty()) {
                continue;
            }

            if (line.front() == '<' && line.back() == '>') {
                // Section header
                currentSection = line.substr(1, line.size() - 2);
            }
            else if (line.find("<!--") == 0) {
                // Comment
                auto endPos = line.find("-->");
                if (endPos == std::string::npos) {
                    // Invalid line
                    continue;
                }
                auto comment = line.substr(4, endPos - 4);
                xmlStructure.comments[currentSection].push_back(comment);
            }
            else {
                // Key-value pair
                auto equalPos = line.find('=');
                if (equalPos == std::string::npos) {
                    // Invalid line
                    continue;
                }
                auto key = line.substr(0, equalPos);
                auto value = line.substr(equalPos + 1);
                xmlStructure.settingData[currentSection][key] = value;
            }
        }
        file.close();
        return true;
    }
    return false;
}

void XmlSetting::addComment(const std::string& section, const std::string& comment)
{
    xmlStructure.comments[section].push_back(comment);
}

CELL_NAMESPACE_END

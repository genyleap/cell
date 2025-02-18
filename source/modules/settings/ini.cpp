#if __has_include("ini.hpp")
#   include "ini.hpp"
#else
#   error "Cell's "ini.hpp" was not found!"
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
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Settings)

IniSetting::IniSetting()
{
}

IniSetting::~IniSetting()
{
}

bool IniSetting::read(const std::string& filename)
{
    iniStructure.filename = filename;
    auto fileIO = FileManager();
    auto file = fileIO.get(iniStructure.filename.value());
    if (!file.is_open()) {
        (DeveloperMode::IsEnable) ? Log("Error opening file " + filename , LoggerType::Critical) : DO_NOTHING;
        return false;
    }
    std::string line;
    std::string current_section;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == ';') {
            // Ignore blank lines and comments
            continue;
        }
        if (line[0] == '[' && line.back() == ']') {
            // This is a section header
            current_section = line.substr(1, line.size() - 2);
            continue;
        }
        // Split the line into key and value
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            // Add the key-value pair to the IniData map
            iniStructure.settingData[current_section][key] = value;
        } else {
            // Invalid line format
            (DeveloperMode::IsEnable) ? Log("Error parsing line in file " + filename , LoggerType::Critical) : DO_NOTHING;
            return false;
        }
    }
    file.close();
    return true;
}

bool IniSetting::save()
{
    auto fileIO = FileManager();
    auto file = fileIO.stream(iniStructure.filename.value());
    if (!file) {
        return false;
    }
    for (auto& section : iniStructure.settingData) {
        if (!iniStructure.comments[section.first].empty()) {
            for (auto& comment : iniStructure.comments[section.first]) {
                file << ";" << comment << std::endl;
            }
        }
        file << "[" << section.first << "]" << std::endl;
        for (auto& key : section.second) {
            if (!iniStructure.comments[section.first + "." + key.first].empty()) {
                for (auto& comment : iniStructure.comments[section.first + "." + key.first]) {
                    file << ";" << comment << std::endl;
                }
            }
            file << key.first << "=" << key.second << std::endl;
        }
        file << std::endl;
    }
    file.close();
    return true;
}

bool IniSetting::getValue(const std::string& section, const std::string& key, std::string& value, const std::string& defaultValue) const
{
    auto sectionIter = std::find_if(iniStructure.settingData.begin(), iniStructure.settingData.end(), [&](const auto& s) {
        return Engine::caseInsensitiveCompare(s.first, section);
    });
    if (sectionIter != iniStructure.settingData.end()) {
        const auto& sectionData = sectionIter->second;

        auto keyIter = std::find_if(sectionData.begin(), sectionData.end(), [&](const auto& k) {
            return Engine::caseInsensitiveCompare(k.first, key);
        });
        if (keyIter != sectionData.end()) {
            value = keyIter->second;
            return true;
        }
    }
    return false;
}

void IniSetting::setValue(const std::string& section, const std::string& key, const std::string& value)
{
    iniStructure.settingData[section][key] = value;
}

void IniSetting::addComment(const std::string& section, const std::string& comment)
{
    if (iniStructure.comments.find(section) == iniStructure.comments.end()) {
        iniStructure.comments[section] = {};
    }
    iniStructure.comments[section].push_back(comment);
}

CELL_NAMESPACE_END

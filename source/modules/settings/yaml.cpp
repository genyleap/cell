#ifdef __has_include
# if __has_include("yaml.hpp")
#   include "yaml.hpp"
#else
#   error "Cell's "yaml.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/filesystem.hpp")
#   include "core/filesystem.hpp"
#else
#   error "Cell's "core/filesystem.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::FileSystem;
CELL_USING_NAMESPACE Cell::eLogger;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Settings)

YamlSetting::YamlSetting()
{
}

YamlSetting::~YamlSetting()
{
}

bool YamlSetting::read(const std::string& filename)
{
    yamlStructure.filename = filename;
    std::ifstream file(filename);
    if (!file) {
        (DeveloperMode::IsEnable) ? Log("Failed to read settings file: " + filename , LoggerType::Critical) : DO_NOTHING;
        return false;
    }
    std::string line;
    std::string current_section;
    while (std::getline(file, line)) {
        // Check for comment
        if (line.size() > 0 && line[0] == '#') {
            yamlStructure.comments[current_section].push_back(line);
            continue;
        }
        // Check for section
        if (line.size() > 0 && line[0] == '-') {
            std::string section = line.substr(1);
            yamlStructure.settingData[section] = std::map<std::string, std::string>{};
            current_section = section;
            yamlStructure.comments[current_section].push_back(line);
            continue;
        }
        // Parse key and value
        std::istringstream ss(line);
        std::string key;
        if (std::getline(ss, key, ':')) {
            std::string value;
            if (std::getline(ss, value)) {
                yamlStructure.settingData[current_section][key] = value;
                yamlStructure.comments[current_section + "." + key] = {};
            }
        }
    }
    return true;
}

bool YamlSetting::save() {
    std::ofstream file(yamlStructure.filename.value());
    if (!file) {
        (DeveloperMode::IsEnable) ? Log("Failed to save settings file: " + yamlStructure.filename.value() , LoggerType::Critical) : DO_NOTHING;
        return false;
    }
    for (const auto& [section, settings] : yamlStructure.settingData) {
        file << "-" << section << std::endl;
        // Write section comments
        if (yamlStructure.comments.count(section) > 0) {
            for (const auto& comment : yamlStructure.comments[section]) {
                file << "# " << comment << std::endl;
            }
        }
        for (const auto& [key, value] : settings) {
            file << key << ": " << value << std::endl;
        }
        file << std::endl;
    }
    return true;
}

bool YamlSetting::get(const std::string& section, const std::string& key, std::string& value, const std::string& defaultValue) const
{
    auto it = yamlStructure.settingData.find(section);
    if (it != yamlStructure.settingData.end()) {
        auto it2 = it->second.find(key);
        if (it2 != it->second.end()) {
            value = it2->second;
            return true;
        }
    }
    value = defaultValue;
    return false;
}

void YamlSetting::setValue(const std::string& section, const std::string& key, const std::string& value)
{
    yamlStructure.settingData[section][key] = value;
    yamlStructure.comments[section + "." + key] = {};
}

void YamlSetting::addComment(const std::string& section, const std::string& comment)
{
    yamlStructure.comments[section].push_back(comment);
}


CELL_NAMESPACE_END

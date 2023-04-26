#ifdef __has_include
# if __has_include("linkparser.hpp")
#   include "linkparser.hpp"
#else
#   error "Cell's "linkparser.hpp" was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Web)

LinkParser::LinkParser()
{
}

LinkParser::~LinkParser()
{
}

void LinkParser::parse(std::string& url)
{
    std::size_t pos   = std::string::npos;
    std::string http  = "http://";
    std::string https = "https://";
    // Search for the substring in string in a loop untill nothing is found
    while((pos = url.find(http))!= std::string::npos || (pos = url.find(https))!= std::string::npos)
    {
        // If found then erase it from string
        if(!url.find(http))
        {
            url.erase(pos, http.length());
        }
        if(!url.find(https))
        {
            url.erase(pos, https.length());
        }
    }
    std::stringstream s(url.starts_with("/") ? url.substr(1,url.length()) : url);
    while (s.good()) {
        std::string substr;
        std::getline(s, substr, '/');
        m_item.push_back(substr);
    }
}

VectorString LinkParser::items()
{
    return m_item;
}

std::string LinkParser::beautify(const std::string& uri)
{
    std::string str = uri;
    for (char& c : str)
    {
        int tmp;
        switch(c) {
        case ' ':
        case '_':
        case ',': tmp = '-'; break;
        case '.': tmp = '_'; break;
        case '+': tmp = 'plus'; break;
        default:
            continue;
        }
        c = tmp;
    }
    std::transform(str.begin(), str.end(), str.begin(), [](char ch) {
        return std::tolower(ch);
    });
    return str;
}

std::string LinkParser::recorrectUrl(std::string& url)
{
    std::regex httpRegex("https?://");
    std::regex wwwRegex("www\\.");
    // Check if URL already has a valid protocol
    if (!std::regex_search(url.begin(), url.end(), httpRegex)) {
        url = "https://" + std::string(url);
    }
    // Remove any redundant "www" subdomains from the URL
    url = std::regex_replace(url.data(), wwwRegex, "");
    // Check if subdomain exists
    std::regex subdomainRegex("https?://\\S+\\.");
    if (!std::regex_search(url.data(), subdomainRegex)) {
        // Add default subdomain "www" if not present
        url = std::regex_replace(url.data(), httpRegex, "https://www.");
    }
    // Return the corrected URL
    return url.data();
}

std::string LinkParser::decodeUrl(const std::string& url)
{
    std::stringstream ss;
    uint value;
    int start = 0, end = 0;
    while ((end = url.find('%', start)) != std::string::npos)
    {
        ss << url.substr(start, end - start);
        if (end + 2 <= url.length()) {
            value = std::stoul(url.substr(end + 1, 2), nullptr, 16);
            ss << static_cast<char>(value);
        }
        start = end + 3;
    }
    ss << url.substr(start);
    return ss.str();
}

CELL_NAMESPACE_END

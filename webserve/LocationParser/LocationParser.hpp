#ifndef LOCATION_PARSER_HPP
#define LOCATION_PARSER_HPP

#include "../lib/ft/ft.hpp"
#include <list>
class LocationParser
{

private:
    std::string	_url;
    std::string	_root;
    std::string	_index;
    std::string	_upload_path;
    std::list<std::string>	_allow_method;
    std::list<std::string>	_try_files;
    bool _auto_index;

    std::string deleteBlock(std::vector<std::string> arr);
    void setUrl(std::string url);
    void setAttributes(std::string body);
    void removeFirstWhiteSpaces(std::vector<std::string> *block_lines);
    bool check_method(std::string method);

public:
    LocationParser();
    LocationParser(const std::string& block);
    LocationParser(const LocationParser& location_parser);
    ~LocationParser();
    LocationParser& operator=(const LocationParser& location_parser);

    std::string getUrl() const;
    std::string getRoot() const;
    std::string getIndex() const;
    std::string getUploadPath() const;
    std::list<std::string> getAllowMethod() const;
    bool getAutoIndex() const;

};

#endif
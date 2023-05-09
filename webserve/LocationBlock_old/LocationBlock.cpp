#include "LocationBlock.hpp"

LocationBlock::LocationBlock()
{
	_url = "";
	_root = "";
	_index = "";
	_upload_path = "";
    _auto_index = false;
}

LocationBlock::LocationBlock(const std::string& block)
{
    std::vector<std::string> arr = ft::splitString(block, "\n");
    std::string head = arr[0];
    std::string body = deleteBlock(arr);
    std::vector<std::string> lines = ft::splitString(body, "\n");
    removeFirstWhiteSpaces(&lines);
    setUrl(head);
    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
        setAttributes(*it);
}

LocationBlock::LocationBlock(const LocationBlock& location_block)
{
    if (this == &location_block)
        return ;
	_url = location_block._url;
	_root = location_block._root;
	_index = location_block._index;
	_upload_path = location_block._upload_path;
    _allow_method = location_block._allow_method;
    _auto_index = location_block._auto_index;
}

LocationBlock::~LocationBlock()
{

}

LocationBlock& LocationBlock::operator=(const LocationBlock& location_block)
{
    if (this == &location_block)
        return (*this);
	_url = location_block._url;
	_root = location_block._root;
	_index = location_block._index;
	_upload_path = location_block._upload_path;
    _allow_method = location_block._allow_method;
    _auto_index = location_block._auto_index;
    return (*this);
}

void LocationBlock::setAttributes(std::string line)
{
    std::string::size_type i = line.find(" ");
    if (i == std::string::npos)
        throw std::exception();
    std::string key = line.substr(0, i);
    std::string value = line.substr(i + 1, line.length() - i - 2);
    if (key.compare("root") == 0)
        _root = value;
    else if (key.compare("index") == 0)
        _index = value;
    else if (key.compare("upload_path") == 0)
        _upload_path = value;
    else if (key.compare("autoindex") == 0)
    {
        if (value.compare("on") == 0)
            _auto_index = true;
        else
            _auto_index = false;
    }
    else if (key.compare("allow_method") == 0)
    {
        std::vector<std::string> methods = ft::splitString(value, " ");
        std::vector<std::string>::iterator it = methods.begin();
        for (;it != methods.end(); it++)
        {
            if (check_method(*it))
                _allow_method.push_back(*it);
        }
    }
    else if (key.compare("try_files") == 0)
    {
        std::vector<std::string> methods = ft::splitString(value, " ");
        std::vector<std::string>::iterator it = methods.begin();
        for (;it != methods.end(); it++)
        {
            if (check_method(*it))
                _allow_method.push_back(*it);
        }
    }
}

void LocationBlock::setUrl(std::string url)
{
    std::vector<std::string> arr = ft::splitString(url, " ");
    _url = arr[1];
}

std::string LocationBlock::deleteBlock(std::vector<std::string> arr)
{
    std::string str;

    std::vector<std::string>::iterator it = arr.begin();
    it++;
    for (; it != arr.end() - 1; it++)
        str += *it + "\n";
    return (str);
}

void LocationBlock::removeFirstWhiteSpaces(std::vector<std::string> *block_lines)
{
	std::vector<std::string>::iterator ite = block_lines->end();

	for (std::vector<std::string>::iterator it = block_lines->begin(); it != ite; it++)
	{
		std::string	line = *it;
		size_t		line_length = line.size();
		size_t		space_end = 0;

		for (; space_end < line_length ; space_end++)
			if(std::isspace(line[space_end], std::locale()) == false)
				break;

		it->erase(0, space_end);
		if (it->empty())
			block_lines->erase(it);
	}
}

bool LocationBlock::check_method(std::string method)
{
    if (method.compare("GET") == 0)
        return (true);
    if (method.compare("POST") == 0)
        return (true);
    if (method.compare("DELETE") == 0)
        return (true);
    return (false);
}

std::string LocationBlock::getUrl() const
{
    return (_url);
}

std::string LocationBlock::getRoot() const
{
    return (_root);
}

std::string LocationBlock::getIndex() const
{
    return (_index);
}

std::string LocationBlock::getUploadPath() const
{
    return (_upload_path);
}

std::list<std::string> LocationBlock::getAllowMethod() const
{
    return (_allow_method);
}

bool LocationBlock::getAutoIndex() const
{
    return (_auto_index);
}
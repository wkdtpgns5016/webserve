#ifndef BLOCK_HPP
# define BLOCK_HPP

#include <iostream>
#include <vector>
#include "../Scripter/Scripter.hpp"

/**
 * @class	Block
 * @brief	Config파일의 기본단위가 되는 클래스
 */
class Parser;

class Block
{
private:
	Block(const Block& other);
	Block& operator= (const Block& other);
protected:
	Scripter	_scripter;
	Parser*	_parser;

	int			_port;
	std::string	_root;
	std::string	_addr;
	std::string	_server_name;
	std::string	_index;
	std::string	_default_error_page;
	int			_client_body_size;

	std::string	_upload_path;
	std::vector<std::string>	_allow_methods;
	std::vector<std::string>	_try_files;
	bool	_autoindex;

	std::vector<Block*>	_inner_blocks;
public:
	Block();
	virtual	~Block();
	virtual	Block*	generateInnerBlock(const std::string& script) = 0;

	void	compile(const std::string& script);

	std::pair<std::string, std::string>	divideSimpleIdAndValue(const std::string& str, size_t pos) const;
	std::pair<std::string, std::string>	divideBlockIdAndValue(const std::string& str, size_t pos) const;

	size_t	parseSimple(const std::string& script);
	void	parseInnerBlock(const std::vector<std::string>& block_scripts);
	
	
	void	copyWithoutInnerBlock(const Block&);

	void	setPort(int port);
	void	setRoot(const std::string& root);
	void	setAddr(const std::string& addr);
	void	setServerName(const std::string& server_name);
	void	setIndex(const std::string& index);
	void	setDefaultErrorPage(const std::string& default_error_page);
	void	setClientBodySize(int client_body_size);
	void	setUploadPath(const std::string& upload_path);
	void	setAllowMethod(const std::string& allow_method);
	void	setTryFiles(const std::string& try_files);
	void	setAutoIndex(bool auto_index);

	void	clearAllowMethod();
	void	clearTryFiles();

	const int&			getPort() const;
	const std::string&	getRoot() const;
	const std::string&	getAddr() const;
	const std::string&	getServerName() const;
	const std::string&	getIndex() const;
	const std::string&	getDefaultErrorPage() const;
	const int&			getClientBodySize() const;
	const std::string&	getUploadPath() const;
	const std::vector<std::string>&	getAllowMethod() const;
	const std::vector<std::string>&	getTryFiles() const;
	const bool&	getAutoindex() const;
	const std::vector<Block *>&	getInnerBlock() const;
};

#include "../Parser/Parser.hpp"

#endif

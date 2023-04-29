#ifndef BLOCK_HPP
# define BLOCK_HPP

#include <iostream>
#include <vector>

///@file	Block.hpp
///@brief	시험작성
class Block
{
private:
	void	(Block::*_parsing_func[11])(const std::string&);

	Block(const Block& other);
	Block& operator= (const Block& other);
protected:
	int			_port;
	std::string	_root;
	std::string	_addr;
	std::string	_server_name;
	std::string	_index;
	std::string	_default_error_page;
	int			_client_body_size;

	std::string	_upload_path;
	std::vector<std::string>	_allow_method;
	std::vector<std::string>	_try_files;
	bool	_autoindex;

	std::vector<Block*>	_inner_blocks;
public:
	Block();
	virtual	~Block();
	virtual	Block*	generateInnerBlock(const std::string& script) = 0;

	void	compile(const std::string& script);

	size_t	jumpTrash(const std::string& str, size_t pos) const;
	size_t	jumpSimple(const std::string& str, size_t pos) const;
	size_t	jumpBlock(const std::string& str, size_t pos) const;
	size_t	jumpBlockId(const std::string& str, size_t pos) const ;
	size_t	jumpWord(const std::string& str, size_t pos) const;

	std::pair<std::string, std::string>	divideSimpleIdAndValue(const std::string& str, size_t pos) const;
	std::pair<std::string, std::string>	divideBlockIdAndValue(const std::string& str, size_t pos) const;

	size_t	parseSimple(const std::string& script);
	virtual size_t	parseInnerBlock(const std::string& script);
	
	void	parsePort(const std::string&);
	void	parseRoot(const std::string&);
	void	parseServerName(const std::string&);
	void	parseIndex(const std::string&);
	void	parseDefaultErrorPage(const std::string&);
	void	parseClientBodySize(const std::string&);
	void	parseUploadPath(const std::string&);
	void	parseAllowMethod(const std::string&);
	void	parseTryFiles(const std::string&);
	void	parseAutoindex(const std::string&);
	void	parseNoMatchId(const std::string&);
	
	void	copyWithoutInnerBlock(const Block&);
	void	setParsingFunctionArray();

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

#endif

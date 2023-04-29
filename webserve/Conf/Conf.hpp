#ifndef CONF_HPP
# define CONF_HPP

#include "../Block/Block.hpp"
#include "../ServerBlock/ServerBlock.hpp"

class Conf : Block
{
public:
	Conf();
	Conf(const Conf& other);
	Conf& operator=(const Conf& other);
	~Conf();
	Conf(const std::string& script);
	ServerBlock*	generateInnerBlock(const std::string& script);
	

};

#endif

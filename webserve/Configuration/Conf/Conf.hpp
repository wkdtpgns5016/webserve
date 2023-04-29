#ifndef CONF_HPP
# define CONF_HPP

#include "../Block/Block.hpp"
#include "../ServerBlock/ServerBlock.hpp"

class Conf : public Block
{
private:
	Conf(const Conf& other);
	Conf& operator=(const Conf& other);
public:
	Conf(const std::string& script);
	ServerBlock*	generateInnerBlock(const std::string& script);

	Conf();
	~Conf();
};

#endif

#include "Conf.hpp"

Conf::Conf() {}
Conf::~Conf()
{
	std::vector<Block *>::iterator ite = _inner_blocks.end();
	for (std::vector<Block *>::iterator it; it != ite; it++)
		delete *it;
}
Conf& Conf::operator=(const Conf& other)
{
	if (&other == this)
		return *this;
	static_cast<Block &>(*this) = other;
	return *this;
}

Conf::Conf(const Conf& other)
{
	if (&other == this)
		return ;
	*this = other;
}

Conf::Conf(const std::string& script) : Block(script)
{
}

ServerBlock*	Conf::generateInnerBlock(const std::string& script)
{
	std::pair<std::string, std::string> id_value_pair = divideBlockIdAndValue(script, 0);

	if (id_value_pair.first != "server")
		throw std::exception();
	return new ServerBlock(*this, script);
}

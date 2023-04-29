#include "Conf.hpp"
#include "../ServerBlock/ServerBlock.hpp"

//script Constructor
Conf::Conf(const std::string& script)
{
	compile(script);
}


//generater
ServerBlock*	Conf::generateInnerBlock(const std::string& script)
{
	std::pair<std::string, std::string> id_value_pair = divideBlockIdAndValue(script, 0);
	std::string	id = id_value_pair.first;
	std::string	value = id_value_pair.second;

	if (id != "server")
		throw std::exception();
	return new ServerBlock(*this, value);
}


//OCCF
Conf::Conf() {}
Conf::~Conf() {}

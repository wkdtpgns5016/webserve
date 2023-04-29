#ifndef SERVERBLOCK_HPP
# define SERVERBLOCK_HPP

#include "../Block/Block.hpp"
#include "../LocationBlock/LocationBlock.hpp"

class ServerBlock : public Block
{
private:
	ServerBlock(const ServerBlock&);
	ServerBlock& operator=(const ServerBlock&);
public:
	ServerBlock(const Block&, const std::string&);
	LocationBlock*	generateInnerBlock(const std::string&);
	std::pair<std::pair<std::string, std::string>, std::string>	divideLocationBlockIdAndValue(const std::string&, size_t );
	
	ServerBlock();
	~ServerBlock();
};

#endif

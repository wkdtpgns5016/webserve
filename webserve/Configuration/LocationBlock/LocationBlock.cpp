#include "LocationBlock.hpp"

//script constructor
LocationBlock::LocationBlock(const Block& outer_block, const std::string& script, const std::string& url) : _url(url)
{
	copyWithoutInnerBlock(outer_block);
	compile(script);
}

//generateInnerBlock
Block*	LocationBlock::generateInnerBlock(const std::string& script)
{
	throw std::exception();
	if (script.empty() || 1)
		return new LocationBlock();
}

const std::string& LocationBlock::getUrl() const { return _url; }

//OCCF
LocationBlock::LocationBlock() {}
LocationBlock::~LocationBlock() {}

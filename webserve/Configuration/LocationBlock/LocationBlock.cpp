#include "LocationBlock.hpp"
#include <string>

//script constructor
LocationBlock::LocationBlock(const Block& outer_block, const std::string& script, const std::string& url) : _url(url)
{
	copyWithoutInnerBlock(outer_block);
	compile(script);
}

//generateInnerBlock
Block*	LocationBlock::generateInnerBlock(const std::string& script)
{
	std::string id = divideBlockIdAndValue(script, 0).first;
	throw UnknownOrNotAllowed(id);
}

const std::string& LocationBlock::getUrl() const { return _url; }

//OCCF
LocationBlock::LocationBlock() {}
LocationBlock::~LocationBlock() {}

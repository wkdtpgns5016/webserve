#ifndef LOCATION_BLOCK_HPP
#define LOCATION_BLOCK_HPP

#include "../Block/Block.hpp"

class LocationBlock : public Block
{
private:
	std::string	_url;

	LocationBlock(const LocationBlock&);
    LocationBlock& operator=(const LocationBlock&);
public:
    LocationBlock(const Block& outer_block, const std::string& script, const std::string& url);
	Block*	generateInnerBlock(const std::string& script);

	const std::string& getUrl() const;

	LocationBlock();
    ~LocationBlock();
};

#endif

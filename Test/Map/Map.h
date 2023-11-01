#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <format>

class Map
{
public:
	void RenderMap();
private:
	struct WrapVector2i
	{
		sf::Vector2i v;
		bool operator==(const WrapVector2i& pt2) const
		{
			return this->v.x == pt2.v.x && this->v.y == pt2.v.y;
		}
	};

	struct WrapVector2iHasher
	{
		bool operator()(const WrapVector2i& vec) const
		{
			return std::hash<int>()(vec.v.x) ^ std::hash<int>()(vec.v.y);
		}
	};

	std::unordered_map<WrapVector2i, std::string, WrapVector2iHasher> allChunks;
	bool stateLoadUpload = true;
	const uint8_t CHUNK_DELIMETR = 32;
};
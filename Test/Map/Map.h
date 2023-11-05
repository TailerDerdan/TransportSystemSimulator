#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <format>
#include <cstdlib>
#include <ctime>
#include <type_traits>

class Map
{
public:
	void RenderMap(bool LoadUpload);

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

	void CryptChunk(sf::Vector2i coords, std::string& chunk);
	void DecryptChunk(std::string& chunk);
	

	template <std::integral T>
	std::string NumToChars(T v)
	{
		std::string l;
		size_t sz = size_t(sizeof(v) / sizeof(char));
		for (size_t i = 0; i < sz; i++)
		{
			l += uint8_t(v);
			v = v >> 8;
		}
		return l;
	}
};
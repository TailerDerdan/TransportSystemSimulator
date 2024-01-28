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
#include "../Utility/Utility.h"

class Decoder
{
public:
	void RenderMap(bool LoadUpload);

private:

	std::unordered_map<WrapVector2i, std::string, WrapVector2iHasher> allChunks;
	bool stateLoadUpload = true;
	const uint8_t CHUNK_DELIMETR = 32;
	const char START_CHARACTER = ' ';

	void CryptChunk(sf::Vector2i coords, std::string& chunk);
	void DecryptChunk(std::ifstream& file);
	
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

	uint32_t CharsToNum(std::string str)
	{
		uint32_t num = 0;
		for (size_t i = 0; i < str.length(); i++)
		{
			num += uint8_t(str[str.length() - i - 1]);
			if (i < 3)
			{
				num = num << 8;
			}
		}
		return num;
	}
};
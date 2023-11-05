#include "Map.h"

//<spacebar> AABBBBDD... CCCC, where AA - amount of bytes;
//BBBB - key, which crypts all data;
//DD... - crypted chunk data;
//CCCC - control summ that equals ~(AA + BBBB + DD..) + 1, where "~" - bit inversion;
//all letters - A, B, D, C - BYTES
void Map::CryptChunk(sf::Vector2i coords, std::string & chunk)
{
	std::string coordX = NumToChars(coords.x);
	std::string coordY = NumToChars(coords.y);

	chunk = coordX + coordY + chunk;

	std::srand(std::time(nullptr));
	uint32_t key = std::rand();

	uint32_t controlSum = 0;
	for (uint8_t ch : chunk)
	{
		controlSum += ch;
	}
	
	for (size_t i = 0; i < chunk.length(); i++)
	{
		chunk[i] ^= key;
	}

	std::string keyAsChar = NumToChars(key);
	chunk = keyAsChar + chunk;

	uint16_t amountOfData = chunk.length();
	for (uint8_t ch : NumToChars(amountOfData))
	{
		controlSum += ch;
	}

	controlSum = ~controlSum + 1;
	chunk = " " + NumToChars(amountOfData) + chunk + NumToChars(controlSum);
	std::cout << std::format("Key: {}, AmountOfData: {}, ControlSum: {}\n", key, amountOfData, controlSum);
}

void Map::DecryptChunk(std::string& chunk)
{

}

void Map::RenderMap(bool LoadUpload)
{
	stateLoadUpload = LoadUpload;

	if (stateLoadUpload)
	{
		std::ifstream file;
		file.open("DATA.txt", std::ios::binary);
		if (!file.is_open())
		{
			std::cout << "Can't open data file!\n";
			return;
		}

		while (!file.eof())
		{
			unsigned char ch;

			file.read((char*)&ch, sizeof(uint8_t));
			
			std::string chunk;

			if (ch == ' ')
			{
				uint32_t sumBytes = 0;

				uint16_t amountBytes = 0; 
				file.read((char*)&amountBytes, sizeof(uint16_t));

				uint32_t cryptKey = 0;
				file.read((char*)&cryptKey, sizeof(uint32_t));
				
				for (uint16_t data = 0; data < amountBytes; data++)
				{
					file.read((char*)&ch, sizeof(char));
					ch = ch ^ cryptKey;
					chunk.push_back(ch);
					sumBytes += uint8_t(ch);
				}

				std::string x = chunk.substr(0, 4);
				std::string y = chunk.substr(4, 4);
				

				uint32_t controlSum = 0;
				std::string cs = chunk.substr(chunk.length() - 4, 4);

				for (size_t i = 0; i < cs.length(); i++)
				{
					controlSum += cs[cs.length() - i];
					controlSum = controlSum << 8;
				}

				if (controlSum != ~(sumBytes)+1)
				{
					return;
				}
			}
			else
			{
				return;
			}
			//allChunks.emplace(std::pair());
		}
		stateLoadUpload = false;
	}
	else
	{
		allChunks.emplace(sf::Vector2i{ 1651, 193212 }, "abaabbabababababababaaabab");
		allChunks.emplace(sf::Vector2i{ -1231, -666 }, "sa121212sajjsajasjasasjhass");

		std::ofstream file;
		file.open("DATA.txt", std::ios::trunc);

		for (auto iter : allChunks)
		{
			std::string chunk = iter.second;
			sf::Vector2i coords = iter.first.v;
			CryptChunk(coords, chunk);
			file << chunk;
		}
		allChunks.clear();
	}
}
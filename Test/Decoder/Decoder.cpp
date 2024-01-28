#include "Decoder.h"

//<spacebar> AABBBBDD... CCCC, where AA - amount of bytes;
//BBBB - key, which crypts all data;
//DD... - crypted chunk data;
//CCCC - control summ that equals ~(AA + BBBB + DD..) + 1, where "~" - bit inversion;
//all letters - A, B, D, C - BYTES
void Decoder::CryptChunk(sf::Vector2i coords, std::string& chunk)
{
	std::string coordX = NumToChars(coords.x);
	std::string coordY = NumToChars(coords.y);

	chunk = coordX + coordY + chunk;

	std::srand(uint32_t(std::time(nullptr)));
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

	uint16_t amountOfData = uint16_t(chunk.length());
	for (uint8_t ch : NumToChars(amountOfData))
	{
		controlSum += ch;
	}

	for (uint8_t ch : keyAsChar)
	{
		controlSum += ch;
	}

	controlSum = ~controlSum + 1;
	chunk = START_CHARACTER + NumToChars(amountOfData) + chunk + NumToChars(controlSum);
}

void Decoder::DecryptChunk(std::ifstream& file)
{
	while (!file.eof())
	{
		unsigned char ch;

		file.read((char*)&ch, sizeof(uint8_t));

		std::string chunk;

		if (ch != START_CHARACTER)
		{
			return;
		}

		uint32_t sumBytes = 0;

		uint16_t amountBytes = 0;
		file.read((char*)&amountBytes, sizeof(uint16_t));

		for (uint8_t ch : NumToChars(amountBytes))
		{
			sumBytes += ch;
		}

		uint32_t cryptKey = 0;
		file.read((char*)&cryptKey, sizeof(uint32_t));

		for (uint8_t ch : NumToChars(cryptKey))
		{
			sumBytes += ch;
		}

		for (uint16_t data = 0; data < amountBytes; data++)
		{
			file.read((char*)&ch, sizeof(char));
			ch = ch ^ cryptKey;
			chunk.push_back(ch);
			if (data < amountBytes - sizeof(sumBytes))
			{
				sumBytes += uint8_t(ch);
			}
		}

		uint32_t controlSum = 0;
		std::string controlSumStr = chunk.substr(chunk.length() - 4, 4);

		std::transform(controlSumStr.begin(), controlSumStr.end(), controlSumStr.begin(), [cryptKey](unsigned char ch) { return ch ^ cryptKey; });

		controlSum = CharsToNum(controlSumStr);
		WrapVector2i coords;
		coords.v.x = CharsToNum(chunk.substr(0, 4));
		coords.v.y = CharsToNum(chunk.substr(4, 4));

		if (controlSum != (~sumBytes + 1))
		{
			return;
		}
		chunk.erase(chunk.length() - 4, 4);
		chunk.erase(0, 8);

		allChunks.emplace(std::pair(coords, chunk));
	}
}

void Decoder::RenderMap(bool LoadUpload)
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
		DecryptChunk(file);
		stateLoadUpload = false;
	}
	else
	{
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
#include "Map.h"

void Map::RenderMap()
{
	std::ifstream file;
	file.open("DATA.txt", std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Can't open data file!\n";
		return;
	}

	if (stateLoadUpload)
	{
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
				amountBytes = (amountBytes >> 8) | (amountBytes << 8);

				sumBytes += amountBytes;

				uint32_t cryptKey = 0;
				file.read((char*)&cryptKey, sizeof(uint32_t));
				cryptKey = (cryptKey >> 24) | (cryptKey << 24) | (cryptKey >> 16 << 24 >> 16) | (cryptKey << 16 >> 24 << 16);
				
				sumBytes += cryptKey;
				
				for (uint16_t data = 0; data < amountBytes; data++)
				{
					file.read((char*)&ch, sizeof(char));
					ch = ch ^ cryptKey;
					chunk.push_back(ch);
					sumBytes += uint8_t(ch);
				}
				uint32_t controlSum = 0;
				file.read((char*)&controlSum, sizeof(uint32_t));
				controlSum = (controlSum >> 24) | (controlSum << 24) | (controlSum >> 16 << 24 >> 16) | (controlSum << 16 >> 24 << 16);				

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
		for (auto iter : allChunks)
		{
			std::string chunk;
			uint16_t amountBytes = 0;
			for (auto ch : chunk)
			{
				amountBytes += ch;
			}
			chunk.push_back(uint8_t(amountBytes >> 8));
			chunk.push_back(uint8_t(amountBytes));

		}
	}
}
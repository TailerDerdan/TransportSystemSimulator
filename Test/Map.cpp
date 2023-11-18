#include "Map.h"

Map::Map()
{
	if (allChunks.empty())
	{
		int x = 0;
		int y = 0;
		std::string emptyChunk;
		for (int iter = 0; iter < 121; iter++)
		{
			emptyChunk.push_back(char(TileAssociation::Grass));
		}
		for (x = -RADIUS_RENDER; x < RADIUS_RENDER; x++)
			for (y = -RADIUS_RENDER; y < RADIUS_RENDER; y++)
			{
				if (x * x + y * y == RADIUS_RENDER * RADIUS_RENDER)
				{
					WrapVector2i vect;
					vect.v.x = x;
					vect.v.y = y;
					allChunks.emplace(std::pair(vect, emptyChunk));
				}
			}
	}
}

void Map::Update()
{
	if (allChunks.empty())
	{

	}
}
#include "Map.h"
#include <random>

void Map::TransfromStrToChunk(std::unordered_map<WrapVector2i, std::string>::iterator chunk, size_t indexOfBuffer)
{
	std::vector<sf::Vertex> vertecies;
	sf::Vector2f chunkPos = sf::Vector2f{ chunk->first.v };
	chunkPos.x *= SIZE_CHUNK;
	chunkPos.x -= RADIUS_RENDER;
	chunkPos.y *= SIZE_CHUNK;
	chunkPos.y -= RADIUS_RENDER;
	uint32_t i = 0;
	for (auto tile : chunk->second)
	{
		sf::Vector2f pos = { float(i % SIZE_CHUNK), float(i / SIZE_CHUNK) };
		sf::Vertex v[4] = {
			{ CartesianToIsometric(sf::Vector2f{ 0.0f, 0.0f } + chunkPos + pos, SIZE_TILE_IN_PIXEL)},
			{ CartesianToIsometric(sf::Vector2f{ 1.0f, 0.0f } + chunkPos + pos, SIZE_TILE_IN_PIXEL)},
			{ CartesianToIsometric(sf::Vector2f{ 1.0f, 1.0f } + chunkPos + pos, SIZE_TILE_IN_PIXEL)},
			{ CartesianToIsometric(sf::Vector2f{ 0.0f, 1.0f } + chunkPos + pos, SIZE_TILE_IN_PIXEL)},
		};
		float r = 0.0;

		if (tile == char(TileAssociation::Grass))
		{
			r = 1;
		}
		else
		{
			r = 2;
		}

		v[0].texCoords = sf::Vector2f{ SIZE_TILE_IN_PIXEL * (r - 1), 0.0f };
		v[1].texCoords = sf::Vector2f{ SIZE_TILE_IN_PIXEL * r, 0.0f };
		v[2].texCoords = sf::Vector2f{ SIZE_TILE_IN_PIXEL * r, SIZE_TILE_IN_PIXEL };
		v[3].texCoords = sf::Vector2f{ SIZE_TILE_IN_PIXEL * (r - 1), SIZE_TILE_IN_PIXEL };
		i++;

		for (size_t i = 0; i < 4; i++)
		{
			vertecies.push_back(v[i]);
		}
	}
	visibleChunks[indexOfBuffer].update(vertecies.data());
}

Map::Map(Camerman* m_ptrCamerman, Chunks chunks): m_ptrCamerman(m_ptrCamerman), allChunks(chunks)
{
	//Load texture
	if (!m_texture.loadFromFile("images/tileset.png"))
	{
		std::cout << "\nCan't load texture!\n";
	}

	if (allChunks.empty())
	{
		int x = 0;
		int y = 0;
		// Create empty chank template
		for (int iter = 0; iter < SIZE_CHUNK * SIZE_CHUNK; iter++)
		{
			emptyChunk.push_back(char(TileAssociation::Grass));
		}

		// Place empty chunks if needed to unorderd_map
		for (x = -RADIUS_RENDER; x <= RADIUS_RENDER; x++)
		{
			for (y = -RADIUS_RENDER; y <= RADIUS_RENDER; y++)
			{
				WrapVector2i vect;
				vect.v.x = x;
				vect.v.y = y;
				allChunks.emplace(std::pair(vect, emptyChunk));
			}
		}
	}

	//Create all vertex buffers
	uint32_t amountOfVerticesPerBuffer = SIZE_CHUNK * SIZE_CHUNK * 4;
	for (size_t i = 0; i < unsigned(RADIUS_RENDER * RADIUS_RENDER * 4); i++)
	{
		sf::VertexBuffer buf;
		buf.create(amountOfVerticesPerBuffer);
		buf.setPrimitiveType(sf::Quads);
		buf.setUsage(sf::VertexBuffer::Usage::Stream);
		visibleChunks.push_back(buf);
	}
}

void Map::Update()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 2);
	std::string randomChunk;
	for (int iter = 0; iter < SIZE_CHUNK * SIZE_CHUNK; iter++)
	{
		int r = dist(mt);
		char tile;
		if (r == 1)
		{
			tile = char(TileAssociation::Grass);
		}
		else
		{
			tile = char(TileAssociation::Trollface);
		}
		randomChunk.push_back(tile);
	}

	centralCoordsNew = m_ptrCamerman->GetCenterCoordOfChunk();
	if (centralCoordsNew != centralLastCoords)
	{
		size_t index = 0;
		for (int i = -RADIUS_RENDER + centralCoordsNew.x; i < (centralCoordsNew.x + RADIUS_RENDER); i++)
		{
			for (int j = -RADIUS_RENDER + centralCoordsNew.y; j < (centralCoordsNew.y + RADIUS_RENDER); j++)
			{
				auto chunk = allChunks.find(WrapVector2i{ sf::Vector2i{ i, j } });
				if (chunk == allChunks.end())
				{
					allChunks.emplace(std::pair(WrapVector2i{ sf::Vector2i{ i, j } }, randomChunk));
				}
				chunk = allChunks.find(WrapVector2i{ sf::Vector2i{ i, j } });
				TransfromStrToChunk(chunk, index);
				index++;
			}
		}
	}
	centralLastCoords = centralCoordsNew;
}

void Map::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_texture;
	for (auto i : visibleChunks)
	{
		target.draw(i, states);
	}
}

Map::~Map()
{}
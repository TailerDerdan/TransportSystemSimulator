#include "Map.h"

void Map::TransfromStrToChunk(std::unordered_map<WrapVector2i, std::string>::iterator chunk)
{
	std::vector<sf::Vertex> vertecies;
	sf::VertexBuffer chunkVertexs;
	sf::Vector2f chunkPos = sf::Vector2f{ chunk->first.v };
	chunkPos.x *= SIZE_CHUNK;
	chunkPos.y *= SIZE_CHUNK;
	uint32_t i = 0;
	for (auto tile : chunk->second)
	{
		sf::Vector2f pos = { float(i % SIZE_CHUNK), float(i / SIZE_CHUNK) };
		sf::Vertex v[4] = {
			{ CartesianToIsometric(sf::Vector2f{ 0.0f, 0.0f } + chunkPos + pos, SIZE_TILE_IN_PIXEL), sf::Color::Green },
			{ CartesianToIsometric(sf::Vector2f{ 1.0f, 0.0f } + chunkPos + pos, SIZE_TILE_IN_PIXEL), sf::Color::Green },
			{ CartesianToIsometric(sf::Vector2f{ 1.0f, 1.0f } + chunkPos + pos, SIZE_TILE_IN_PIXEL), sf::Color::Green },
			{ CartesianToIsometric(sf::Vector2f{ 0.0f, 1.0f } + chunkPos + pos, SIZE_TILE_IN_PIXEL), sf::Color::Green },
		};

		v[0].texCoords = sf::Vector2f{ 0.0f, 0.0f };
		v[1].texCoords = sf::Vector2f{ SIZE_TILE_IN_PIXEL, 0.0f };
		v[2].texCoords = sf::Vector2f{ SIZE_TILE_IN_PIXEL, SIZE_TILE_IN_PIXEL };
		v[3].texCoords = sf::Vector2f{ 0.0f, SIZE_TILE_IN_PIXEL };
		i++;

		for (size_t i = 0; i < 4; i++)
		{
			vertecies.push_back(v[i]);
		}
	}
	chunkVertexs.create(vertecies.size());
	chunkVertexs.update(vertecies.data());
	chunkVertexs.setPrimitiveType(sf::Quads);
	chunkVertexs.setUsage(sf::VertexBuffer::Usage::Stream);
	visibleChunks.push_back(chunkVertexs);
}

Map::Map(Camerman* m_ptrCamerman, Chunks chunks): m_ptrCamerman(m_ptrCamerman), allChunks(chunks)
{
	visibleChunks.resize(RADIUS_RENDER * RADIUS_RENDER);
	if (allChunks.empty())
	{
		int x = 0;
		int y = 0;
		for (int iter = 0; iter < SIZE_CHUNK * SIZE_CHUNK; iter++)
		{
			emptyChunk.push_back(char(TileAssociation::Grass));
		}
		for (x = -RADIUS_RENDER; x < RADIUS_RENDER; x++)
			for (y = -RADIUS_RENDER; y < RADIUS_RENDER; y++)
			{
				if (x * x + y * y <= RADIUS_RENDER * RADIUS_RENDER)
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
	centralCoordsNew = m_ptrCamerman->GetCenterCoordOfChunk();
	if (centralCoordsNew != centralLastCoords)
	{
		for (int i = -RADIUS_RENDER + centralCoordsNew.x; i <= (centralCoordsNew.x + RADIUS_RENDER); i++)
		{
			for (int j = -RADIUS_RENDER + centralCoordsNew.x; j <= (centralCoordsNew.x + RADIUS_RENDER); j++)
			{
				auto chunk = allChunks.find(WrapVector2i{ sf::Vector2i{ i, j } });
				if (chunk == allChunks.end())
				{
					allChunks.emplace(std::pair(WrapVector2i{ sf::Vector2i{i, j} }, emptyChunk));
				}
				chunk = allChunks.find(WrapVector2i{ sf::Vector2i{ i, j } });
				TransfromStrToChunk(chunk);
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
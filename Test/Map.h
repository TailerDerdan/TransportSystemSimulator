#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Utility/Utility.h"
#include "Const/Const.h"
#include "CameraMan/Camerman.h"
#include <format>

using Chunks = std::unordered_map<WrapVector2i, std::string, WrapVector2iHasher>;

class Map
{
public:
	Map(Camerman* m_ptrCamerman, Chunks chunks);
	~Map();
	void Update();

	enum class TileAssociation
	{
		Grass = 'A',
		Trollface = 'T',
	};

	void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int GetSizeAllChunks()
	{
		return allChunks.size();
	}

private:

	void TransfromStrToChunk(std::unordered_map<WrapVector2i, std::string>::iterator chunk, size_t indexOfBuffer);

	Chunks allChunks;
	sf::Vector2i centralLastCoords = {-1, -1};
	std::vector<sf::VertexBuffer> visibleChunks;
	Camerman* m_ptrCamerman = nullptr;
	const uint8_t RADIUS_RENDER = 4;
	sf::Vector2i centralCoordsNew;

	std::string emptyChunk;

	sf::Texture m_texture;
};
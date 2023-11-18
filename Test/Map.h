#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Utility/Utility.h"

class Map
{
public:
	Map();
	~Map();
	void Update();

	enum class TileAssociation
	{
		Grass = 'A'
	};

private:

	std::unordered_map<WrapVector2i, std::string> allChunks;
	sf::Vector2i centralCoords;
	sf::Vector2i centralLastCoords;
	std::vector<sf::VertexBuffer> visibleChunks;
	sf::RenderWindow* m_ptrWindow;
	const uint8_t RADIUS_RENDER = 2;
};
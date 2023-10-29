#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.h"
#include <vector>

class Cube
{
public:
	Cube();
	~Cube();
	void SetCube(sf::Vector2f pos, float size, sf::Color col);
	void Draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	struct Info
	{
		const static uint32_t Size = 100;
	};

private:
	std::vector<sf::Vertex> m_verteces;
	sf::Vector2f m_gridPos;
	sf::Texture m_tileset;
};


#include "Cube.h"

void Cube::SetCube(sf::Vector2f pos, float size, sf::Color col)
{
	if (!m_tileset.loadFromFile("images/tileset.png"))
	{
		return;
	}

	m_gridPos = pos;

	sf::Vertex v[4] = 
	{
		{ CartesianToIsometric(sf::Vector2f{0.0f, 0.0f} + pos, size), col },
		{ CartesianToIsometric(sf::Vector2f{1.0f, 0.0f} + pos, size), col },
		{ CartesianToIsometric(sf::Vector2f{1.0f, 1.0f} + pos, size), col },
		{ CartesianToIsometric(sf::Vector2f{0.0f, 1.0f} + pos, size), col },
	};

	v[0].texCoords = sf::Vector2f{ 0.0f, 0.0f };
	v[1].texCoords = sf::Vector2f{ size, 0.0f };
	v[2].texCoords = sf::Vector2f{ size, size };
	v[3].texCoords = sf::Vector2f{ 0.0f, size };

	for (size_t i = 0; i < 4; i++)
	{
		m_verteces.push_back(v[i]);
	}
}

void Cube::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_tileset;
	target.draw(m_verteces.data(), m_verteces.size(), sf::Quads, states);
}

Cube::Cube()
{
}

Cube::~Cube()
{
}
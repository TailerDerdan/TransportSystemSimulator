#include "World.h"

World::World()
{
	for (size_t i = 0; i < Info::Size; i++)
	{
		for (size_t j = 0; j < Info::Size; j++)
		{
			m_cubeField[i][j] = nullptr;
		}
	}
}

World::~World()
{
	for (size_t i = 0; i < Info::Size; i++)
	{
		for (size_t j = 0; j < Info::Size; j++)
		{
			delete m_cubeField[i][j];
		}
	}
}

void World::Create()
{
	for (size_t i = 0; i < Info::Size; i++)
	{
		for (size_t j = 0; j < Info::Size; j++)
		{
			m_cubeField[i][j] = new Cube;
			m_cubeField[i][j]->SetCube(sf::Vector2f{ float(i), float(j) }, Cube::Info::Size, sf::Color::Yellow);
		}
	}
}

void World::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < Info::Size; i++)
	{
		for (size_t j = 0; j < Info::Size; j++)
		{
			m_cubeField[i][j]->Draw(target, states);
		}
	}
}
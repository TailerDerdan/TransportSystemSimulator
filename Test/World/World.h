#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.h"
#include "../Cube/Cube.h"

class World
{
public:
	World();
	~World();
	void Create();
	void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	struct Info
	{
		const static uint32_t Size = 11;
	};

private:
	std::array<std::array<Cube*, Info::Size>, Info::Size> m_cubeField;
};


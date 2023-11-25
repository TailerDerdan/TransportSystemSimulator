#pragma once
#include "../Utility/Utility.h"
#include "SFML/Graphics.hpp"
#include "../Cube/Cube.h"
#include "../Const/Const.h"

class Camerman
{
public:
	sf::RenderWindow m_window;

	Camerman();
	~Camerman();
	
	void Update();

	sf::View m_view;

	sf::Vector2f WindowsRealtiveToGridFromMouse()
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos, m_view);
		sf::Vector2f gridCoord = IsometricToCartesian(worldPos, SIZE_TILE_IN_PIXEL);
		return gridCoord;
	}

	sf::Vector2i GetCenterCoordOfChunk()
	{
		sf::Vector2i pixelPos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
		sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos, m_view);
		sf::Vector2f gridCoord = IsometricToCartesian(worldPos, SIZE_TILE_IN_PIXEL);
		return { int(gridCoord.x / SIZE_CHUNK), int(gridCoord.y / SIZE_CHUNK) };
	}

private:
	bool m_dragging = false;
	sf::Vector2i m_previousMousePos;

	float m_curZoom = 1.0f;
	const float MIN_ZOOM = 0.1f;
	const float MAX_ZOOM = 5.0f;

	void CameraInit();
	void EventHandler(sf::Event event);
};


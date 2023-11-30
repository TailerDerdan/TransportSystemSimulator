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
	sf::Vector2i GetCenterCoordOfChunk();
	sf::Vector2f WindowsRealtiveToGridFromMouse();

private:
	bool m_dragging = false;
	sf::Vector2i m_previousMousePos;

	float m_curZoom = 1.0f;
	const float MIN_ZOOM = 0.1f;
	const float MAX_ZOOM = 5.0f;

	void CameraInit();
	void EventHandler(sf::Event event);
};


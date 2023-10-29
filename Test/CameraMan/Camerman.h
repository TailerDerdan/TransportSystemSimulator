#pragma once
#include "../Utility/Utility.h"
#include "SFML/Graphics.hpp"
#include "../Cube/Cube.h"

class Camerman
{
public:
	sf::RenderWindow m_window;

	Camerman();
	~Camerman();
	
	void Update();
	
private:
	sf::View m_view;

	bool m_dragging = false;
	sf::Vector2i m_previousMousePos;

	float m_curZoom = 1.0f;
	const float MIN_ZOOM = 0.4f;
	const float MAX_ZOOM = 2.0f;

	void CameraInit();
	void EventHandler(sf::Event event);

	sf::Vector2f WindowsRealtiveToGrid();
};


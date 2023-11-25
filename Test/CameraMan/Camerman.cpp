#include "../CameraMan/Camerman.h"
#include <iostream>
#include <string>
#include "../Const/Const.h"

void Camerman::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		EventHandler(event);
	}
}

void Camerman::CameraInit()
{
	m_view.reset(sf::FloatRect({ -325.0f, -200.0f }, { WINDOW_WIDTH, WINDOW_HEIGHT }));
	m_window.setView(m_view);
}

void Camerman::EventHandler(sf::Event event)
{
	sf::Vector2i coordBefore;
	switch (event.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;

	case sf::Event::MouseWheelMoved:
		m_curZoom += -event.mouseWheel.delta * 0.2f;
		if (m_curZoom > MAX_ZOOM)
		{
			m_curZoom = MAX_ZOOM;
		}

		if (m_curZoom < MIN_ZOOM)
		{
			m_curZoom = MIN_ZOOM;
		}

		m_view.setSize(WINDOW_WIDTH * m_curZoom, WINDOW_HEIGHT * m_curZoom);
		m_view.zoom(m_curZoom);
		m_window.setView(m_view);
		break;

	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f gridCoord = WindowsRealtiveToGridFromMouse();
			m_window.setTitle("X: " + std::to_string(gridCoord.x) + "; Y: " + std::to_string(gridCoord.y));
			
		}

		if (event.mouseButton.button == sf::Mouse::Right)
		{
			m_dragging = true;
			coordBefore = sf::Mouse::getPosition(m_window);
		}
		break;

	case sf::Event::MouseButtonReleased:
		m_dragging = false;
		break;

	case sf::Event::MouseMoved:
		sf::Vector2i mousePos{ event.mouseMove.x, event.mouseMove.y };
		if (m_dragging)
		{
			sf::Vector2f delta = m_window.mapPixelToCoords(mousePos) - m_window.mapPixelToCoords(m_previousMousePos);
			m_view.move(-delta);
			m_window.setView(m_view);
		}
		m_previousMousePos = mousePos;
		break;
	}
}

Camerman::Camerman()
{
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulator");
	CameraInit();
}

Camerman::~Camerman()
{
}
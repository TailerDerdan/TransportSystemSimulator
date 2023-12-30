#include "Map.h"
#include "CameraMan/Camerman.h"
#include "Utility/Utility.h"
#include <string>

int main()
{
	Camerman mainCam;
	Chunks ch;
	Map mappa(&mainCam, ch);

	sf::Clock clock;
	float fps = 0.0f;

	while (mainCam.m_window.isOpen())
	{
		float curTime = clock.restart().asSeconds();
		fps = 1.0f / curTime;
		mainCam.Update();
		mainCam.m_window.clear(sf::Color(255, 255, 255, 255));
		mappa.Update();
		mappa.Draw(mainCam.m_window, sf::RenderStates::Default);
		mainCam.m_window.display();

		mainCam.m_window.setTitle(std::format("{} fps", fps));
	}

    return 0;
}
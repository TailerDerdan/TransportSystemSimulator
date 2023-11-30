#include "Map.h"
#include "CameraMan/Camerman.h"
#include "Utility/Utility.h"
#include <string>

int main()
{
	Camerman mainCam;
	Chunks ch;
	Map mappa(&mainCam, ch);

	while (mainCam.m_window.isOpen())
	{
		mainCam.Update();
		mainCam.m_window.clear(sf::Color(255, 255, 255, 255));
		mappa.Update();
		mappa.Draw(mainCam.m_window, sf::RenderStates::Default);
		mainCam.m_window.display();
		//sf::Vector2i centralCoords = mainCam.GetCenterCoordOfChunk();
		//std::cout << centralCoords.x << " " << centralCoords.y << std::endl;
		std::cout << mappa.GetSizeAllChunks() << std::endl;
	}

   /* World* world = new World;
    world->Create();

    while (mainCam.m_window.isOpen())
	{
		mainCam.Update();
		mainCam.m_window.clear(sf::Color(255, 255, 255, 255));
		world->Draw(mainCam.m_window, sf::RenderStates::Default);

		sf::Vector2i centralCoords = mainCam.GetCenterCoordOfChunk();

		std::cout << centralCoords.x << " " << centralCoords.y << std::endl;

		mainCam.m_window.display();
	}    */

    return 0;
}
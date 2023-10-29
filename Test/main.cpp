#include "World/World.h"
#include "CameraMan/Camerman.h"
#include "Utility/Utility.h"
#include <string>

int main()
{
    Camerman mainCam;

    World* world = new World;
    world->Create();

    while (mainCam.m_window.isOpen())
    {
        mainCam.Update();
        mainCam.m_window.clear(sf::Color(255, 255, 255, 255));
        world->Draw(mainCam.m_window, sf::RenderStates::Default);

        mainCam.m_window.display();
    }

    return 0;
}
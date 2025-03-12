#include "Controller.h"

Controller::Controller()
	: m_gameManager(m_window)
{
	m_window.create(sf::VideoMode(800, 600), "Zombies Ate My Neighbors");

}

Controller::~Controller()
{
}

void Controller::run()
{
	m_gameManager.run();
	/*while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		m_window.clear();
		m_window.display();
	}*/
}

/*
* Controller.h
* start the program and control switches between screens
* not responsible for the gameplay itself
*/
#pragma once
#include "GameManager.h"

class Controller
{
public:
	Controller();
	~Controller();

	void run();

private:
	sf::RenderWindow m_window;
	GameManager m_gameManager;
};
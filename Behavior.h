#pragma once
#include <SFML/Graphics.hpp>

class Behavior
{
public:
	virtual ~Behavior() {};
	virtual void execute(float dt) = 0;
};
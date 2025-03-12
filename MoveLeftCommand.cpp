#include "Commands/MoveLeftCommand.h"

MoveLeftCommand::MoveLeftCommand(Player& mobileObject, Player::Action action)
	: m_mobileObject(mobileObject), m_action(action)
{
}

void MoveLeftCommand::execute(float dt)
{
	m_mobileObject.move(sf::Vector2f(-1.0f, 0.0f), dt);
}

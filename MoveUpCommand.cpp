#include "Commands/MoveUpCommand.h"

MoveUpCommand::MoveUpCommand(Player& mobileObject, Player::Action action)
	: m_mobileObject(mobileObject), m_action(action)
{
}

void MoveUpCommand::execute(float dt)
{
	m_mobileObject.move(sf::Vector2f(0.0f, -1.0f), dt);
}
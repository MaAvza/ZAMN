#pragma once
#include "Command.h"
#include "Objects/MobileObjects/Player.h"

class MoveUpCommand : public Command
{
public:
	MoveUpCommand(Player& mobileObject, Player::Action action);
	~MoveUpCommand() = default;

	void execute(float dt) override;

private:
	Player& m_mobileObject;
	Player::Action m_action;
};
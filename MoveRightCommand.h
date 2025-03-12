#pragma once
#include "Command.h"
#include "Objects/MobileObjects/Player.h"

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(Player& mobileObject, Player::Action action);
	~MoveRightCommand() = default;

	void execute(float dt) override;

private:
	Player& m_mobileObject;
	Player::Action m_action;
};
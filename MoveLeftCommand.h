#pragma once
#include "Command.h"
#include "Objects/MobileObjects/Player.h"

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(Player& mobileObject, Player::Action action);
	~MoveLeftCommand() = default;

	void execute(float dt) override;

private:
	Player& m_mobileObject;
	Player::Action m_action;
};
#pragma once
#include "Command.h"
#include "Objects/MobileObjects/Player.h"

class MoveDownCommand : public Command
{
public:
	MoveDownCommand(Player& mobileObject, Player::Action action);
	~MoveDownCommand() = default;

	void execute(float dt) override;

private:
	Player& m_mobileObject;
	Player::Action m_action;
};

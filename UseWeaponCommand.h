#pragma once
#include "Command.h"
#include "Objects/MobileObjects/Player.h"

class UseWeaponCommand : public Command
{
public:
	UseWeaponCommand(Player& player, Player::Action action);
	~UseWeaponCommand() = default;

	void execute(float dt) override;

private:
	Player& m_player;
	Player::Action m_action;
};
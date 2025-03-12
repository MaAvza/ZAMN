#pragma once
#include "Command.h"
#include "Objects/Inventory.h"
#include "Objects/MobileObjects/Player.h"

class SwitchWeaponCommand : public Command
{
public:
	SwitchWeaponCommand(Inventory& inventory, Player::Action action);

	void execute(float dt) override;

private:
	Inventory& m_inventory;
	Player::Action m_action;
};
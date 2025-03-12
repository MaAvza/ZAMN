#pragma once
#include "Command.h"
#include "Objects/Inventory.h"
#include "Objects/MobileObjects/Player.h"

class ChangeItemCommand : public Command
{
public:
	ChangeItemCommand(Inventory& inventory, Player::Action action);
	~ChangeItemCommand() = default;

	void execute(float dt) override;

private:
	Inventory& m_inventory;
	Player::Action m_action;
};
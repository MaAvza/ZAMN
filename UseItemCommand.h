#pragma once
#include "Command.h"
#include "Objects/Inventory.h"
#include "Objects/MobileObjects/Player.h"

class UseItemCommand : public Command
{
public:
	UseItemCommand(Inventory& inventory, Player::Action action);
	~UseItemCommand() = default;

	void execute(float dt) override;

private:
	Inventory& m_inventory;
	Player::Action m_action;
};
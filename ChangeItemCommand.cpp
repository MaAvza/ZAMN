#include "Commands/ChangeItemCommand.h"

ChangeItemCommand::ChangeItemCommand(Inventory& inventory, Player::Action action)
	: m_inventory(inventory), m_action(action)
{
}

void ChangeItemCommand::execute(float dt)
{
	m_inventory.switchItem();
}

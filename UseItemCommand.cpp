#include "Commands/UseItemCommand.h"

UseItemCommand::UseItemCommand(Inventory& inventory, Player::Action action)
	: m_inventory(inventory), m_action(action)
{
}

void UseItemCommand::execute(float dt)
{
	m_inventory.useItem();
}

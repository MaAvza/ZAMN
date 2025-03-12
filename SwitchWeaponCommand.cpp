#include "Commands/SwitchWeaponCommand.h"

SwitchWeaponCommand::SwitchWeaponCommand(Inventory& inventory, Player::Action action)
	: m_inventory(inventory), m_action(action)
{
}

void SwitchWeaponCommand::execute(float dt)
{
	m_inventory.switchWeapon();
}
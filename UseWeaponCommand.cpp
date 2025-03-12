#include "Commands/UseWeaponCommand.h"

UseWeaponCommand::UseWeaponCommand(Player& player, Player::Action action)
	:m_player(player), m_action(action)
{
}

void UseWeaponCommand::execute(float dt)
{
	m_player.fireWeapon();
}

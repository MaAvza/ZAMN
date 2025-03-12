#include "Objects/Inventory.h"
#include <algorithm>
#include <typeinfo>

Inventory::Inventory()
	:m_items(MAX_ITEMS), m_weapons(MAX_WEAPONS), m_currentWeaponIndex(0), m_currentItemType("")
{
}

bool Inventory::addItem(std::shared_ptr<CollectibleItem> item)
{
	auto it = m_items.find(typeid(*item).name());
	if (it == m_items.end()) {
		m_items[typeid(*item).name()] = std::make_pair(item, 1);
	}
	else {
		it->second.second++;
	}
	return true;
}

bool Inventory::addWeapon(std::shared_ptr<Weapon> weapon)
{
	if (!weapon) {
		return false; // Return false if the weapon is null
	}

	auto it = std::find_if(m_weapons.begin(), m_weapons.end(),
		[&weapon](const std::shared_ptr<Weapon>& w) {
			return w && typeid(*w) == typeid(*weapon); // Check if w is not null before using typeid
		});

	if (it == m_weapons.end()) {
		m_weapons.push_back(weapon);
		return true;
	}
	return false;
}

void Inventory::switchWeapon()
{
	if (!m_weapons.empty()) {
		m_currentWeaponIndex = (m_currentWeaponIndex + 1) % m_weapons.size();
	}
	/*m_currentWeaponIndex = (m_currentWeaponIndex + 1) % m_weapons.size();
        while (!m_weapons[m_currentWeaponIndex] && !isWeaponInventoryEmpty()) {
            m_currentWeaponIndex = (m_currentWeaponIndex + 1) % m_weapons.size();
        }*/
}

void Inventory::switchItem()
{
	if (!m_items.empty()) {
		auto it = m_items.find(m_currentItemType);
		if (it == m_items.end()) {
			it = m_items.begin();
		}
		else {
			++it;
			if (it == m_items.end()) {
				it = m_items.begin();
			}
		}
		m_currentItemType = it->first;
	}
}

bool Inventory::useWeapon()
{
	if (m_weapons.empty()) {
		return false;
	}

	std::string ammoType = getCurrentWeaponAmmoType();
	auto it = m_items.find(ammoType);

	if (it != m_items.end() && it->second.second > 0) {
		// Reduce ammo count
		it->second.second--;

		// Remove the item if count reaches 0
		if (it->second.second == 0) {
			m_items.erase(it);
		}

		return true;
	}

	return false;
}

void Inventory::useItem()
{
	auto it = m_items.find(m_currentItemType);
	if (it != m_items.end()) {
		//it->second.first->onCollect();
		it->second.second--;
		if (it->second.second <= 0) {
			m_items.erase(it);
			switchItem();
		}
	}
}

bool Inventory::useKey()
{
	const std::string keyType = "Key"; // Assuming the type string for Key is "Key"
	auto it = m_items.find(keyType);
	if (it != m_items.end() && it->second.second > 0)
	{
		// Reduce the count of the key
		it->second.second--;

		// If the count reaches zero, remove the key from the inventory
		if (it->second.second == 0)
		{
			m_items.erase(it);
		}

		return true; // Key was successfully used
	}

	return false; 

}

const std::shared_ptr<Weapon>& Inventory::getCurrentWeapon() const
{
	return m_weapons[m_currentWeaponIndex];
}

const std::shared_ptr<CollectibleItem>& Inventory::getCurrentItem() const
{
	static std::shared_ptr<CollectibleItem> nullItem;
	auto it = m_items.find(m_currentItemType);
	if (it != m_items.end()) {
		return it->second.first;
	}
	return nullItem;
}

bool Inventory::isWeaponInventoryEmpty() const
{
	return m_weapons.empty();
}

bool Inventory::isItemInventoryEmpty() const
{
	return m_items.empty();
}

int Inventory::getItemCount(const std::string& itemType) const
{
	auto it = m_items.find(itemType);
	if (it != m_items.end()) {
		return it->second.second;
	}
	return 0;
}

int Inventory::getAmmoCount(const std::string& ammoType) const
{
	return getItemCount(ammoType);
}

std::string Inventory::getCurrentWeaponAmmoType() const
{
	return (m_weapons.empty()) ? "" : m_weapons[m_currentWeaponIndex]->getAmmoType();
}

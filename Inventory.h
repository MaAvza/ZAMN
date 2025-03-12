#pragma once
#include "StaticObjects/CollectibleItem.h"
#include "StaticObjects/FlameThrower.h"
#include "StaticObjects/PelletGun.h"
#include <unordered_map>

class Inventory
{
public:
	Inventory();
	~Inventory() = default;

	bool addItem(std::shared_ptr<CollectibleItem> item);
	bool addWeapon(std::shared_ptr<Weapon> weapon);
	void switchWeapon();
	void switchItem();
	bool useWeapon();
	void useItem();
	bool useKey();

	const std::shared_ptr<Weapon>& getCurrentWeapon() const;
	const std::shared_ptr<CollectibleItem>& getCurrentItem() const;

	bool isWeaponInventoryEmpty() const;
	bool isItemInventoryEmpty() const;
	int getItemCount(const std::string& itemType) const;
	int getAmmoCount(const std::string& ammoType) const;

private:
	std::unordered_map<std::string, std::pair<std::shared_ptr<CollectibleItem>, int>> m_items;
	std::vector<std::shared_ptr<Weapon>> m_weapons;
	size_t m_currentWeaponIndex;
	std::string m_currentItemType;

	std::string getCurrentWeaponAmmoType() const;
};
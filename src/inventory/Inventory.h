#pragma once
#include <bitset>
#include "../states/UIStates.h"
#include "../entity/Entity.h"
#include "../items/Weapon.h"
#include "../items/Gear.h"
#include "../assets/WeaponAssets.h"
#include "../assets/GearAssets.h"
#include "../settings/GlobalSettings.h"
#include "../../base/strings.h"
#include "../../base/misc.h"

enum InventoryTabs : uint8 {
	GEAR,
	WEAPON
};

struct Inventory {
private:
	static inline InventoryTabs _currentTab;
	static inline Rectangle _inventoryWindow;
	static inline Rectangle _inventoryBackButton;

	static inline Rectangle _gearTab;
	static inline Rectangle _gearCells[15];
	static inline Rectangle _verticalGearSlotRects[3];
	static inline Rectangle _lrGearSlotRects[2];

	static inline Rectangle _weaponTab;
	static inline Rectangle _weaponTabSlotRects[5];
	static inline Vector2 _weaponSlotPos;
	static inline bool _selectedWeapon[5];
public:
	// Properties
	static InventoryTabs getCurrentTab() { return _currentTab; }

	// Methods
	static void exitInventory(Vector2 &mousePos, UIStates &uiState);
	static void drawInventory();

	static void selectInventoryTabs(Vector2 &mousePos);
	static void drawGearTab();
	static void drawWeaponTab();

	static void drawSlots();
	static void drawStatArea(Entity &entity);

	static void drawLeftInventory();
	static void drawRightInventory(Entity &entity);

	static void drawCurrentWeapon(Weapon &current);
	static void drawWeapons(Weapon &current, Vector2 &mousePos);
	static bool selectWeapon(Weapon &current, uint8 weaponCount, Vector2 &mousePos);
	static bool equipButton(int8 selectedIdx, Weapon &current, Vector2 &mousePos);
	
	static void drawCurrentGear(std::vector<Gear> currentGear);
	static void drawGear(std::bitset<15> availableGear);
	static bool selectGear(std::bitset<15> availableGear, std::vector<Gear> &currentGear, Vector2 &mousePos);
};
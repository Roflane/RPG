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

class Inventory {
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
	static inline bool	  _selectedWeapon[5];

public:
	Inventory() = default;
	~Inventory() = default;

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

	static void drawWeapons(Weapon &current, Vector2 &mousePos);
	static void drawCurrentWeapon(Weapon &current);
	static bool selectWeapon(Weapon &current, uint8 weaponCount, Vector2 &mousePos);
	static bool equipButton(int8 selectedIdx, Weapon &current, Vector2 &mousePos);
	
	static void drawCurrentGear(std::vector<Gear> currentGear);
	//static bool selectGear(std::vector<Gear> &currentGear, Vector2 &mousePos);

	template<uint8 gearCount>
	static void drawGear(std::bitset<gearCount> availableGear) {
		if (_currentTab == GEAR) {
			for (uint8 i = 0; i < availableGear.size(); ++i) {
				GearAssets::GearList[i].width = _gearCells->width;
				GearAssets::GearList[i].height = _gearCells->height;
				if (availableGear[i]) {
					DrawTexture(GearAssets::GearList[i], _gearCells[i].x, _gearCells[i].y, WHITE);
				}
				else {
					DrawTexture(GearAssets::GearList[i], _gearCells[i].x, _gearCells[i].y, BLACK);
				}
			}
		}
	}
	template<uint8 gearCount>
	static bool selectGear(std::bitset<gearCount> availableGear, std::vector<Gear> &currentGear, Vector2 &mousePos) {
		if (_currentTab == GEAR) {
			for (uint8 i = 0; i < 15; ++i) {
				if (IsClickedOnRect(mousePos, _gearCells[i])) {
					if (availableGear[i]) {
						if (i == T3HEAD || i == T2HEAD || i == T1HEAD) {
							currentGear[HEAD] = static_cast<Gear>(i);
							return true;
						}
						else if (i == T3ARMOR || i == T2ARMOR || i == T1ARMOR) {
							currentGear[ARMOR] = static_cast<Gear>(i);
							return true;
						}
						else if (i == T3BOOTS || i == T2BOOTS || i == T1BOOTS) {
							currentGear[BOOTS] = static_cast<Gear>(i);
							return true;
						}
						else if (i == T3NECKLACE || i == T2NECKLACE || i == T1NECKLACE) {
							currentGear[NECKLACE] = static_cast<Gear>(i);
							return true;
						}
						else if (i == T3RING || i == T2RING || i == T1RING) {
							currentGear[RING] = static_cast<Gear>(i);
							return true;
						}
					}
				}
			}
		}
		return false;
	}
};
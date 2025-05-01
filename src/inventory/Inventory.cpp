#include "Inventory.h"

static Color UIColor = Fade(MAROON, 0.73f);
static Color SelectedCellColor = Fade(BLUE, 0.73f);
static float factorPos = 0.05f, factorSize = 0.1f;
float lineThickness = 3.f;

static float midPos = 0, thinSepY = 0, rightSepX = 0, cellOffset = 0;

void Inventory::exitInventory(Vector2 &mousePos, UIStates &uiState) {
	if (IsClickedOnRect(mousePos, _inventoryBackButton)) {
		_currentTab = GEAR;
		uiState = UIStates::NONE;
	}
}
void Inventory::drawInventory() {
	ClearBackground(WHITE);

	// Main
	_inventoryWindow = {
		.x = 0 + (ScreenSettings::w * factorPos), .y = (ScreenSettings::h * factorPos),
		.width = ScreenSettings::w - (ScreenSettings::w * factorSize), .height = ScreenSettings::h - (ScreenSettings::h * factorSize)
	};
	DrawRectangleRoundedLinesEx(_inventoryWindow, 0.15f, 0, lineThickness, UIColor);

	_inventoryBackButton = {
		.x = ScreenSettings::w * 0.02f, .y = ScreenSettings::h * 0.02f,
		.width = ScreenSettings::w * 0.02f, .height = ScreenSettings::h * 0.04f
	};
	DrawRectangleRoundedLinesEx(_inventoryBackButton, 0.55f, 0, lineThickness, UIColor);

	uint8 closeButtonTextSize = _inventoryBackButton.height;
	DrawText("-", GetTextPosX("-", _inventoryBackButton, closeButtonTextSize), GetTextPosY("X", _inventoryBackButton, closeButtonTextSize), closeButtonTextSize, BLACK);

	// Lines
	midPos = _inventoryWindow.x + _inventoryWindow.width / 2;
	Vector2 midSepStartPos = { midPos, _inventoryWindow.y };
	Vector2 midSepEndPos = { midPos, _inventoryWindow.y + _inventoryWindow.height };
	DrawLineEx(midSepStartPos, midSepEndPos, lineThickness, UIColor);

	thinSepY = _inventoryWindow.y + (_inventoryWindow.height * 0.12f);
	Vector2 thinSepStartPos = { _inventoryWindow.x, thinSepY };
	Vector2 thinSepEndPos = { midSepEndPos.x, thinSepY };
	DrawLineEx(thinSepStartPos, thinSepEndPos, lineThickness / 3, UIColor);

	rightSepX = midPos + (midPos * 0.45f);
	Vector2 rightSepStartPos = { rightSepX, _inventoryWindow.y };
	Vector2 rightSepEndPos = { rightSepX, _inventoryWindow.y + _inventoryWindow.height };
	DrawLineEx(rightSepStartPos, rightSepEndPos, lineThickness / 3, UIColor);

	// Tabs
	_gearTab = {
		.x = _inventoryWindow.x + (_inventoryWindow.width * (factorPos * 2)), .y = _inventoryWindow.y + (_inventoryWindow.height * factorPos),
		.width = _inventoryWindow.width * 0.10f, .height = _inventoryWindow.height * 0.05f
	};
	_weaponTab = {
		.x = (_gearTab.x + _gearTab.width) + (_inventoryWindow.width * (factorPos * 2)), .y = _gearTab.y,
		.width = _gearTab.width, .height = _gearTab.height
	};

	if (_currentTab == GEAR) { DrawRectangleRounded(_gearTab, 0.25f, 0, UIColor); }
	else { DrawRectangleRoundedLinesEx(_gearTab, 0.25f, 0, lineThickness, UIColor); }

	if (_currentTab == WEAPON) { DrawRectangleRounded(_weaponTab, 0.25f, 0, UIColor); }
	else { DrawRectangleRoundedLinesEx(_weaponTab, 0.25f, 0, lineThickness, UIColor); }


	uint8 textSize = _gearTab.width * 0.2f;
	DrawText(TTab::gear, GetTextPosX(TTab::gear, _gearTab, textSize),
		GetTextPosY(TTab::gear, _gearTab, textSize), textSize, BLACK);
	DrawText(TTab::weapon, GetTextPosX(TTab::weapon, _weaponTab, textSize),
		GetTextPosY(TTab::weapon, _weaponTab, textSize), textSize, BLACK);
}

void Inventory::selectInventoryTabs(Vector2 &mousePos) {
	if (IsClickedOnRect(mousePos, _gearTab)) {
		_currentTab = GEAR;
	}
	else if (IsClickedOnRect(mousePos, _weaponTab)) {
		_currentTab = WEAPON;
	}
}
void Inventory::drawLeftInventory() {
	switch (_currentTab) {
		case InventoryTabs::GEAR:   drawGearTab();	 break;
		case InventoryTabs::WEAPON: drawWeaponTab(); break;
	}
}

void Inventory::drawRightInventory(Entity &entity) {
	drawSlots();
	drawStatArea(entity);
}

void Inventory::drawGearTab() {
	cellOffset = (thinSepY * 0.3f);
	Vector2 gearCellStart = {
		.x = _inventoryWindow.x + (cellOffset * 1.5f),
		.y = thinSepY + cellOffset
	};
	Vector2 gearCellSize = {
		.x = ScreenSettings::w * 0.05f,
		.y = ScreenSettings::h * 0.1f
	};
	Rectangle gearCell = {0, 0, 0, 0};

	const uint8 cols = 5;
	const uint8 rows = 3;

	for (uint8 row = 0; row < rows; ++row) {
		for (uint8 col = 0; col < cols; ++col) {
			gearCell.x = gearCellStart.x + col * (gearCellSize.x + cellOffset);
			gearCell.y = gearCellStart.y + row * (gearCellSize.y + cellOffset);
			gearCell.width = gearCellSize.x;
			gearCell.height = gearCellSize.y;

			uint8 index = row * cols + col;
			_gearCells[index] = gearCell;

			DrawRectangleRoundedLinesEx(gearCell, 0.15f, 0, 1.f, UIColor);
		}
	}
}

void Inventory::drawWeaponTab() {
	uint8 weaponCellAmount = 5;

	Vector2 weaponCellSize = {
		ScreenSettings::w * 0.05f, ScreenSettings::h * 0.10f
	};
	Vector2 weaponCellPos = {
		.x = _inventoryWindow.x + (_inventoryWindow.width * 0.25f) - (weaponCellSize.x / 2), .y = thinSepY + cellOffset
	};
	Rectangle weaponCell = {
		.x = weaponCellPos.x, .y = weaponCellPos.y,
		.width = weaponCellSize.x, .height = weaponCellSize.y
	};

	for (uint8 i = 0; i < weaponCellAmount; ++i) {
		_weaponTabSlotRects[i] = weaponCell;
		DrawRectangleRoundedLinesEx(weaponCell, 0.15f, 0, 1.f, UIColor);
		weaponCell.y += weaponCell.height + cellOffset;
	}
}

void Inventory::drawCurrentGear(std::vector<Gear> currentGear) {
	// Vertical gear
	for (uint8 i = 0; i < 3; ++i) {
		if (currentGear[i] != Gear::NONEGEAR) { 
			GearAssets::GearList[currentGear[i]].width = _verticalGearSlotRects->width;
			GearAssets::GearList[currentGear[i]].height = _verticalGearSlotRects->height;
			DrawTexture(GearAssets::GearList[currentGear[i]], _verticalGearSlotRects[i].x, _verticalGearSlotRects[i].y, WHITE);
		}
	}

	// Necklace & Ring
	if (currentGear[3] != Gear::NONEGEAR) {
		GearAssets::GearList[currentGear[3]].width = _lrGearSlotRects->width;
		GearAssets::GearList[currentGear[3]].height = _lrGearSlotRects->height;
		DrawTexture(GearAssets::GearList[currentGear[3]], _lrGearSlotRects[0].x, _lrGearSlotRects[0].y, WHITE);
	}

	if (currentGear[4] != Gear::NONEGEAR) {
		GearAssets::GearList[currentGear[4]].width = _lrGearSlotRects->width;
		GearAssets::GearList[currentGear[4]].height = _lrGearSlotRects->height;
		DrawTexture(GearAssets::GearList[currentGear[4]], _lrGearSlotRects[1].x, _lrGearSlotRects[1].y, WHITE);
	}
}

void Inventory::drawSlots() {
	const uint8 verticalSlots = 3;

	float offset = ScreenSettings::w * 0.01f;
	float gap = _inventoryWindow.height * 0.12f;
	Vector2 slotSize = { _inventoryWindow.width * 0.05f, _inventoryWindow.height * 0.1f };

	Vector2 topSlotPos = {
		.x = midPos + (midPos * 0.25f) - (slotSize.x / 2) - offset,
		.y = _inventoryWindow.y + (_inventoryWindow.y * 0.3f)
	};
	Rectangle topSlot = {
		.x = topSlotPos.x, .y = topSlotPos.y,
		.width = slotSize.x, .height = slotSize.y
	};

	Rectangle leftSlot = {
		.x = topSlot.x - gap, .y = topSlot.y + gap,
		.width = topSlot.width, .height = topSlot.height
	};
	Rectangle rightSlot = {
		.x = topSlot.x + gap, .y = topSlot.y + gap,
		.width = topSlot.width, .height = topSlot.height
	};
	_lrGearSlotRects[0] = leftSlot;
	_lrGearSlotRects[1] = rightSlot;
	DrawRectangleRoundedLinesEx(leftSlot, 0.2f, 0, 1.f, UIColor);
	DrawRectangleRoundedLinesEx(rightSlot, 0.2f, 0, 1.f, UIColor);

	for (uint8 i = 0; i < verticalSlots; ++i) {
		DrawRectangleRoundedLinesEx(topSlot, 0.2f, 0, 1.f, UIColor);
		_verticalGearSlotRects[i] = topSlot;
		topSlot.y += gap;
	}

	topSlot.y += gap / 2;
	topSlot.width *= 1.33f;
	topSlot.height *= 1.33f;
	topSlot.x -= topSlot.width * 0.1f;
	_weaponSlotPos = { topSlot.x, topSlot.y };
	DrawRectangleRoundedLinesEx(topSlot, 0.2f, 0, 1.f, UIColor);
}
void Inventory::drawStatArea(Entity &entity) {
	const uint8 statCount = 8;

	float textOffset = _inventoryWindow.height * 0.15f;
	float statFontSize = _inventoryWindow.height * 0.03f;

	Vector2 statTextPos = {
		.x = rightSepX + (_inventoryWindow.width * 0.1f),
		.y = _inventoryWindow.y + (_inventoryWindow.height * 0.05f)
	};
	DrawText("Stats", statTextPos.x, statTextPos.y, ScreenSettings::w * 0.03f, BLACK);
	statTextPos.y += textOffset / 4;

	const char *statFormat[statCount] = {
		"HP: %.2f", "Attack: %.2f", "Defense: %.2f",
		"Extra damage bonus: %.2f", "Extra damage reduction: %.2f",
		"Crit rate: %.2f", "Crit damage: %.2f", "Crit damage reduction: %.2f"
	};

	const Stats &stats = entity.getStat();
	const float *statValues[5] = {
		&stats.hp, &stats.atk, &stats.def, &stats.edb, &stats.edr
	};

	uint8 i = 0;
	for (; i < 5; ++i) {
		DrawText(TextFormat(statFormat[i], *statValues[i]), statTextPos.x - textOffset,
			statTextPos.y + ((i + 1) * (textOffset / 4)), statFontSize, BLACK);
	}
	DrawText(TextFormat(statFormat[5], *&stats.cr), statTextPos.x - textOffset,
		statTextPos.y + ((i + 1) * (textOffset / 4)), statFontSize, BLACK);
	DrawText(TextFormat(statFormat[6], *&stats.cd), statTextPos.x - textOffset,
		statTextPos.y + ((i + 2) * (textOffset / 4)), statFontSize, BLACK);
	DrawText(TextFormat(statFormat[7], *&stats.cdr), statTextPos.x - textOffset,
		statTextPos.y + ((i + 3) * (textOffset / 4)), statFontSize, BLACK);
}

float newWeaponW, newWeaponH;
void Inventory::drawWeapons(Weapon &current, Vector2 &mousePos) {
	newWeaponW = ScreenSettings::w * 0.05f;
	newWeaponH = ScreenSettings::h * 0.1f;

	static uint8 frameDelay = 8;
	static uint8 frameCounter = 0;
	static uint8 currentIdx = 0;

	frameCounter++;
	if (frameCounter >= frameDelay) {
		frameCounter = 0;
		currentIdx++;
		if (currentIdx >= 5) currentIdx = 0;
	}

	if (_currentTab == WEAPON)
		for (uint8 i = 0; i < 2; ++i) {
			if (IsCursorOnRect(mousePos, _weaponTabSlotRects[i])) {
				WeaponAssets::CurrentAnimationList[i][currentIdx].width = newWeaponW;
				WeaponAssets::CurrentAnimationList[i][currentIdx].height = newWeaponH;
				Texture2D &currentFrame = WeaponAssets::CurrentAnimationList[i][currentIdx];
				DrawTexture(currentFrame, _weaponTabSlotRects[i].x, _weaponTabSlotRects[i].y, WHITE);
			}
			else {
				WeaponAssets::WeaponList[i].width = newWeaponW;
				WeaponAssets::WeaponList[i].height = newWeaponH;
				DrawTexture(WeaponAssets::WeaponList[i], _weaponTabSlotRects[i].x,
					_weaponTabSlotRects[i].y, WHITE);
			}
		}
}
void Inventory::drawCurrentWeapon(Weapon &current) {
	float offsetX = (ScreenSettings::h * 0.01f);
	for (size_t i = 0; i < WeaponAssets::WeaponList.size(); ++i) {
		if (current == i) {
			WeaponAssets::WeaponList[i].width = newWeaponW;
			WeaponAssets::WeaponList[i].height = ScreenSettings::h * 0.1f;
			DrawTexture(WeaponAssets::WeaponList[i], _weaponSlotPos.x + offsetX, _weaponSlotPos.y + offsetX, WHITE);
		}
	}
}

bool Inventory::selectWeapon(Weapon &current, uint8 weaponCount, Vector2 &mousePos) {
	static int8 selectedIdx = -1;

	if (_currentTab == WEAPON) {
		for (uint8 i = 0; i < weaponCount; ++i) {
			if (IsClickedOnRect(mousePos, _weaponTabSlotRects[i])) {
				if (selectedIdx != -1) {
					_selectedWeapon[selectedIdx] = false;
				}
				_selectedWeapon[i] = true;
				selectedIdx = i;
			}
		}

		if (selectedIdx != -1) {
			DrawRectangleRoundedLinesEx(_weaponTabSlotRects[selectedIdx], 0.15f, 0, lineThickness, SelectedCellColor);
			if (equipButton(selectedIdx, current, mousePos)) {
				//printn("true");
				return true;
			}
		}
	}
	return false;
}
bool Inventory::equipButton(int8 selectedIdx, Weapon &current, Vector2 &mousePos) {
	Rectangle equipButton = {
		.x = (_weaponTabSlotRects[selectedIdx].x + _weaponTabSlotRects[selectedIdx].width) + (ScreenSettings::w * 0.01f), .y = _weaponTabSlotRects[selectedIdx].y,
		.width = _weaponTabSlotRects[selectedIdx].width * 0.2f , .height = _weaponTabSlotRects[selectedIdx].height * 0.2f
	};
	DrawRectangleRounded(equipButton, 0.25f, 0, GREEN);

	if (IsClickedOnRect(mousePos, equipButton)) {
		current = static_cast<Weapon>(selectedIdx);
		return true;
	}
	return false;
}
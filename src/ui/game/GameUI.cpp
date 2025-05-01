#include "GameUI.h"

static float inventoryTextX = 0, inventoryTextY = 0;
static float inventoryTextSize = 0;

void GameUI::drawButtons() {
	DrawRectangleRounded(_inventoryButton, 0.25f, 0, Fade(MAROON, 0.73f));
	DrawText(TButton::inventory, inventoryTextX, inventoryTextY, inventoryTextSize, BLACK);
}
void GameUI::updateButtons() {
	float buttonSize = ScreenSettings::h * 0.05f;
	Vector2 inventoryButtonPos = {
		.x = ScreenSettings::w - (ScreenSettings::w * 0.03f) - buttonSize,
		.y = ScreenSettings::h * 0.03f
	};
	_inventoryButton = {
		.x = inventoryButtonPos.x, .y = inventoryButtonPos.y,
		.width = buttonSize, .height = buttonSize
	};

	inventoryTextSize = _inventoryButton.height;
	uint16 measureText = MeasureText(TButton::inventory, inventoryTextSize);
	inventoryTextX = _inventoryButton.x + (_inventoryButton.width / 2) - (measureText / 2);
	inventoryTextY = _inventoryButton.y + (_inventoryButton.height * 0.05f);
}

void GameUI::changeUIState(Vector2 &mousePos) {
	if (IsClickedOnRect(mousePos, _inventoryButton)) {
		_uiState = UIStates::INVENTORY;
	}
}
void GameUI::handleUIState() {
	switch (_uiState) {
		case NONE:		drawButtons(); break;
		case INVENTORY: Inventory::drawInventory(); break;
	}
}
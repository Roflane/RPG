#pragma once
#include "../../states/UIStates.h"
#include "../../entity/Entity.h"
#include "../../inventory/Inventory.h"
#include "../../settings/GlobalSettings.h"
#include "../../../base/strings.h"
#include "../../../base/misc.h"

class GameUI {
private:
	inline static UIStates _uiState = UIStates::NONE;
	inline static Rectangle _inventoryButton;
public:
	// Properties
	static UIStates& getUIState() 		   { return _uiState; }
	static void setUIState(UIStates value) { _uiState = value; }

	// Methods
	static void drawButtons();
	static void updateButtons();

	static void changeUIState(Vector2 &mousePos);
	static void handleUIState();
};
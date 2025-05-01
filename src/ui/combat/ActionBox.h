#pragma once
#include <raylib.h>
#include "../../assets/MiscAssets.h"
#include "../../settings/GlobalSettings.h"
#include "../../../base/dirs.h"
#include "../../../base/strings.h"
#include "../../../base/misc.h"

enum class ActionOption : uint8 {
	SELECTION,
	ATTACK,
	MAGIC,
	ITEM
};

enum class InternalOption : uint8 {
	NONE,
	BA,
	EA,
	BM,
	EM
};

class ActionBox {
private:
	ActionOption _currentOption;
	Rectangle _backButton;

	Rectangle _actionBox;
	Rectangle _attackButton;
	Rectangle _magicButton;
	Rectangle _itemButton;
	
	Rectangle _internalBA;
	Rectangle _internalEA;
	Rectangle _internalBM;
	Rectangle _internalEM;
public:
	ActionBox();
	~ActionBox() = default;
	
	// Properties
	ActionOption& getCurrentOptionRef()			{ return _currentOption; }
	ActionOption getCurrentOption() const		{ return _currentOption; }
	void setCurrentOption(ActionOption option)	{ _currentOption = option; };

	// Methods
	void draw(Color color);
	void update();

	void drawOptions(Color color);

	void drawInternalAttackOptions();
	void drawInternalMagicOptions();
	InternalOption handleInternalOptions(Vector2 &mousePos);

	void selectOptions(Vector2 &mousePos);
	void handleSelectSound(Vector2 &mousePos);
	void handleOptions();
};
#pragma once
#include "../../../base/misc.h"
#include "../../../base/strings.h"
#include "../../../base/typedefs.h"
#include "../../settings/GlobalSettings.h"
#include "../../particles/Parallax.h"

struct MenuButtons {
	Rectangle startButton;
	Rectangle loadButton;
	Rectangle exitButton;
};

class MainMenu : public Parallax {
private:
	Color _bgColor;
	MenuButtons _menuButtons;
	Parallax _parallax;
public:
	MainMenu(Color bgColor, uint16 count, uint16 scrollSpeed, Color color) : Parallax(count, scrollSpeed, color) {
		_bgColor = bgColor;
		_menuButtons = {};
	}
	
	// Methods
	void Display();
	void Update(float dt);

	bool StartGame(Vector2 mousePos);
	bool ExitGame(Vector2 mousePos);
};
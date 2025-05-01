#include "MainMenuUI.h"

static float buttonW, buttonH;
static Vector2 buttonPos;
static uint8 roundness;
static Color buttonColor;
static float fontSize;

void MainMenu::Update(float dt) {
	buttonW = ScreenSettings::w * 0.1f;
	buttonH = ScreenSettings::h * 0.05f;
	buttonPos = { ScreenSettings::centerX - (buttonW / 2),  ScreenSettings::centerY + (ScreenSettings::centerY / 4) };

	roundness = ScreenSettings::w * 0.01f;
	buttonColor = RED;

	_menuButtons.startButton = {
		.x = buttonPos.x, .y = buttonPos.y,
		.width = buttonW, .height = buttonH
	};
	_menuButtons.exitButton = {
		.x = buttonPos.x, .y = buttonPos.y + (ScreenSettings::h * 0.08f),
		.width = buttonW, .height = buttonH
	};
	//_menuButtons.exitButton = {
	//	.x = buttonPos.x, .y = _menuButtons.loadButton.y + (ScreenSettings::h * 0.08f),
	//	.width = buttonW, .height = buttonH
	//};

	fontSize = ScreenSettings::h * 0.05f;

	Parallax::Update(dt);
}

void MainMenu::Display() {
	ClearBackground(_bgColor);

	Parallax::Draw();

	Rectangle screen = {0, 0, ScreenSettings::w, ScreenSettings::h};
	DrawText(TMainMenu::title, GetTextPosX(TMainMenu::title, screen, fontSize), GetTextPosY(TMainMenu::title, screen, fontSize), fontSize, WHITE);

	DrawRectangleRounded(_menuButtons.startButton, roundness, 0, buttonColor);
	DrawText(TMainMenu::start, GetTextPosX(TMainMenu::start, _menuButtons.startButton, fontSize), GetTextPosY(TMainMenu::start, _menuButtons.startButton, fontSize), fontSize, BLACK);

	DrawRectangleRounded(_menuButtons.exitButton, roundness, 0, buttonColor);
	DrawText(TMainMenu::exit, GetTextPosX(TMainMenu::exit, _menuButtons.exitButton, fontSize), GetTextPosY(TMainMenu::exit, _menuButtons.exitButton, fontSize), fontSize, BLACK);

	//DrawRectangleRounded(_menuButtons.exitButton, roundness, 0, buttonColor);
	//DrawText(TMainMenu::exit, GetTextPosX(TMainMenu::exit, _menuButtons.exitButton, fontSize), GetTextPosY(TMainMenu::exit, _menuButtons.exitButton, fontSize), fontSize, BLACK);
}

bool MainMenu::StartGame(Vector2 mousePos) {
	if (IsClickedOnRect(mousePos, _menuButtons.startButton)) { return true; }
	return false;
}
bool MainMenu::ExitGame(Vector2 mousePos) {
	if (IsClickedOnRect(mousePos, _menuButtons.exitButton)) { return true; }
	return false;
}
#include "ActionBox.h"

static Color commonColor = Fade(WHITE, 0.5f);
static Color textColor = Fade(BLACK, 0.73f);

static float buttonW, buttonH;
static float offsetX, offsetY;

static Vector2 button1Pos, button2Pos, button3Pos;
static float textSize;

ActionBox::ActionBox()
    : _currentOption(ActionOption::SELECTION),
    _backButton(),
    _actionBox(),
    _attackButton(), _magicButton(), _itemButton(),
    _internalBA(), _internalEA(), _internalBM(), _internalEM() {}

void ActionBox::draw(Color color) {
	DrawRectangleRounded(_actionBox, 0.25f, 0, commonColor);

    if (_currentOption != ActionOption::SELECTION) {
        DrawRectangleRounded(_backButton, 0.25f, 0, commonColor);
        DrawTexture(MiscAssets::backButtonSprite, _backButton.x + (_backButton.width / 2) - (MiscAssets::backButtonSprite.width / 2),
            _backButton.y + (_backButton.height / 2) - (MiscAssets::backButtonSprite.height / 2), WHITE);
    }
}
void ActionBox::update() {
    int8 factor = 5;
    float actionBoxW = ScreenSettings::w / factor;
    float actionBoxH = ScreenSettings::h / factor;

    Vector2 actionBoxPos = {
        .x = ScreenSettings::centerX - (actionBoxW / 2),
        .y = ScreenSettings::centerY + (ScreenSettings::centerY / 2)
    };
    _actionBox = {
        .x = actionBoxPos.x, .y = actionBoxPos.y,
        .width = actionBoxW, .height = actionBoxH
    };

    _backButton = {
         .x = actionBoxPos.x + actionBoxW - (offsetX * 2), .y = actionBoxPos.y + (offsetY / 2),
         .width = actionBoxW / 10, .height = actionBoxH / 10
    };

    buttonW = _actionBox.width * 0.4f;
    buttonH = _actionBox.height * 0.2f;
    offsetX = (_actionBox.width - buttonW) / 6;
    offsetY = _actionBox.height * 0.15f;

    button1Pos = {
        .x = _actionBox.x + offsetX,
        .y = _actionBox.y + offsetY
    };
    button2Pos = {
        .x = button1Pos.x,
        .y = button1Pos.y + buttonH + (_actionBox.height * 0.05f)
    };
    button3Pos = {
        .x = button2Pos.x,
        .y = button2Pos.y + buttonH + (_actionBox.height * 0.05f)
    };

    textSize = buttonW / 4;
}

void ActionBox::selectOptions(Vector2 &mousePos) {
    if (IsClickedOnRect(mousePos, _backButton)) {
        _currentOption = ActionOption::SELECTION;
    }
    else if (IsClickedOnRect(mousePos, _attackButton) && _currentOption == ActionOption::SELECTION) {
        _currentOption = ActionOption::ATTACK;
    }
    else if (IsClickedOnRect(mousePos, _magicButton) && _currentOption == ActionOption::SELECTION) {
        _currentOption = ActionOption::MAGIC;
    }
}
void ActionBox::handleSelectSound(Vector2 &mousePos) {
    if (IsClickedOnRect(mousePos, _backButton) || 
        IsClickedOnRect(mousePos, _attackButton) ||
        IsClickedOnRect(mousePos, _magicButton)) {
            PlaySound(GameSettings::orbSound);
    }

}
void ActionBox::handleOptions() {
    switch (_currentOption) {
        case ActionOption::SELECTION: drawOptions(WHITE); break;
        case ActionOption::ATTACK:    drawInternalAttackOptions(); break;
        case ActionOption::MAGIC:     drawInternalMagicOptions(); break;
        case ActionOption::ITEM:      break;
    }
}

void ActionBox::drawOptions(Color color) {
    _attackButton = { .x = button1Pos.x, .y = button1Pos.y, .width = buttonW, .height = buttonH };
    _magicButton = { .x = button2Pos.x, .y = button2Pos.y, .width = buttonW, .height = buttonH };
    _itemButton = { .x = button3Pos.x, .y = button3Pos.y, .width = buttonW, .height = buttonH };

    DrawRectangleRounded(_attackButton, 0.25f, 0, commonColor);
    DrawText(TActionOptions::attack, GetTextPosX(TActionOptions::attack, _attackButton, textSize), _attackButton.y, textSize, textColor);

    DrawRectangleRounded(_magicButton, 0.25f, 0, commonColor);
    DrawText(TActionOptions::magic, GetTextPosX(TActionOptions::magic, _magicButton, textSize), _magicButton.y, textSize, textColor);

    // DrawRectangleRounded(_itemButton, 0.25f, 0, commonColor);
    // DrawText(TActionOptions::item, GetTextPosX(TActionOptions::item, _itemButton, textSize), _itemButton.y, textSize, textColor);
}

void ActionBox::drawInternalAttackOptions() {
    _internalBA = { .x = button1Pos.x, .y = button1Pos.y, .width = buttonW, .height = buttonH };
    _internalEA = { .x = button2Pos.x, .y = button2Pos.y, .width = buttonW, .height = buttonH };

    DrawRectangleRounded(_internalBA, 0.25f, 0, commonColor);
    DrawText(TInternalOptions::basicAttack, GetTextPosX(TInternalOptions::basicAttack, _internalBA, textSize), _internalBA.y, textSize, textColor);

    DrawRectangleRounded(_internalEA, 0.25f, 0, commonColor);
    DrawText(TInternalOptions::enhancedAttack, GetTextPosX(TInternalOptions::enhancedAttack, _internalEA, textSize), _internalEA.y, textSize, textColor);
}

void ActionBox::drawInternalMagicOptions() {
    _internalBM = { .x = button1Pos.x, .y = button1Pos.y, .width = buttonW, .height = buttonH };
    _internalEM = { .x = button2Pos.x, .y = button2Pos.y, .width = buttonW, .height = buttonH };

    DrawRectangleRounded(_internalBM, 0.25f, 0, commonColor);
    DrawText(TInternalOptions::basicMagic, GetTextPosX(TInternalOptions::basicMagic, _internalBM, textSize), _internalBM.y, textSize, textColor);

    DrawRectangleRounded(_internalEM, 0.25f, 0, commonColor);
    DrawText(TInternalOptions::enhancedMagic, GetTextPosX(TInternalOptions::enhancedMagic, _internalEM, textSize), _internalEM.y, textSize, textColor);
}

InternalOption ActionBox::handleInternalOptions(Vector2 &mousePos) {
    switch (_currentOption) {
        case ActionOption::ATTACK:
            if (IsClickedOnRect(mousePos, _internalBA)) { return InternalOption::BA; }
            else if (IsClickedOnRect(mousePos, _internalEA)) { return InternalOption::EA; }
            break;
        case ActionOption::MAGIC:
            if (IsClickedOnRect(mousePos, _internalBM)) { return InternalOption::BM; }
            else if (IsClickedOnRect(mousePos, _internalEM)) { return InternalOption::EM; }
            break;
    }
    return InternalOption::NONE;
}
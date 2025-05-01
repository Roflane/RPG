#pragma once
#define init_seed srand(time(0));
#define running !WindowShouldClose()
#include <raylib.h>

#include "entity/Player.h"
#include "entity/Foe.h"
#include "map/Map.h"

#include "ui/game/MainMenuUI.h"
#include "ui/game/GameUI.h"
#include "ui/combat/Gauge.h"
#include "ui/combat/ActionBox.h"
#include "particles/Star.h"

#include "battle/Battle.h"

#include "states/GameState.h"

#include "stats/InitEntityData.h"
#include "inventory/Inventory.h"
#include "assets/MiscAssets.h"
#include "../base/dirs.h"


#define DEEPBLUE CLITERAL(Color){ 5, 5, 35, 1 } 


class GameUtils {
protected:
    GameUtils(bool isGamePaused) : __isGamePaused(isGamePaused) {}

    // Fields
    bool __isGamePaused;

    // Methods
    void DrawFps(Color color);
    void AnimatedCursor(Vector2 pos, float dt);
};

class Game : GameUtils {
private:
    GameState _gameState;
public:
    Game() : GameUtils(false), _gameState(EXPLORING) {}

    // Properties
    GameState getGameState() const         { return _gameState; }
    void setGameState(GameState gameState) { _gameState = gameState; }

    // Methods
    void Menu();
    void Run();
    
    void SwitchPauseState();
    void DrawPauseState();

    void DrawStars(Star &stars, float fallSpeed);

    void InitMap(Map &map);
    void UpdateMap(Map &map);

    void InitCam(Camera2D &main);
    void UpdateCam(Camera2D &main, Player &wipung);
    
    void InitPlayer(Player &wipung, Map &map);
    void UpdatePlayer(Player &wipung, Map &map, float dt);

    void InitFoe(Foe &foe, Map &map);
    void UpdateFoe(Foe &foe);

    void DrawUI(Player &player, Vector2 &mousePos);
    void HandleUI(Player &player, Vector2 &mousePos);

    void UpdateGauges(InitEntityData &initEntityData, Player &player, Foe &enemy);
    void UpdateActionBox(ActionBox &actionBox, Vector2 &mousePos);

    void ProcessBattleUi(ActionBox &actionBox, Star &stars, InitEntityData &initEntityData, Player &player, Foe &enemy, Vector2 &mousePos);
    void ProcessBattleLogic(ActionBox &actionBox, Battle &battle, Player &player, Foe &enemy, Vector2 &mousePos, Camera2D &main);

    bool BattleEnterAnimation(Camera2D &cam, Player &wipung, Foe &enemy, float dt);
    void StartBattle(Camera2D &cam, Player &player, Foe &enemy, float dt);

    void GetEntityData(InitEntityData &initEntityData, Player &player, Foe &enemy);
    void UpdateEntityData(Player &player, Foe &enemy);

    void GenerateNextMap(Map &map, Battle &battle);
    void GenerateNextEnemy(Battle &battle, Foe& enemy);
};
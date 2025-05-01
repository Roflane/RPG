#pragma once
#include "../../base/typedefs.h"
#include "../entity/Entity.h"
#include "../entity/Player.h"
#include "../entity/Foe.h"
#include "../states/GameState.h"
#include "../ui/combat/ActionBox.h"

#define win enemy.getStat().hp <= 0
#define lose player.getStat().hp <= 0

enum class BattleTurn : uint8 {
	UNDEFINED, 
	PLAYER,
	ENEMY
};

struct BattleData {
	// Fields
	inline static BattleTurn currentTurn = BattleTurn::UNDEFINED;
	inline static uint8 currentLevel = 1;
	inline static uint8 maxLevels = 10;
	inline static bool battleFinished = false;
};

class Battle {
private:
	BattleData _battleData;
public:
	Battle() : _battleData() {}

	// Properties
	void setBattleFinished(bool value) { _battleData.battleFinished = value; }
	BattleData getBattleData() const   { return _battleData; }

	// Methods
	void updateEntities(Player &player, Foe &enemy);
	void updateState(Player &player, Foe &enemy, GameState &gameState, Camera2D &main);

	bool handlePlayerAnimations(Player &player, InternalOption &internalOption, GameState &gameState);
	bool handleEnemyAnimations(Foe &enemy, GameState &gameState);
	void handleBattleAnimations(ActionBox &actionBox, Player &player, Foe &enemy, GameState &gameState);

	void manageInternalOption(ActionBox &actionBox, Vector2 &mousePos);
	void battleLoop(Player &player, Foe &enemy, GameState &gameState, Vector2 &mousePos);

	void generateEnemyPattern();
};
#include "Battle.h"
#include "../animations/FoeAnimations.h"

static PlayerAnimations playerAnimations;
static FoeAnimations foeAnimations;

static uint8 maxLevel = 10;
static InternalOption internalChoice = InternalOption::NONE;
static bool playerAnimating = false, enemyAnimating = false;
static uint8 enemyOption;

void Battle::updateEntities(Player &player, Foe &enemy) {
    Vector2 enemyPos = { ScreenSettings::w - (ScreenSettings::w * 0.2f), ScreenSettings::centerY };
    enemy.setPos(enemyPos);
    if (!enemyAnimating) foeAnimations.KIdle(enemy.getSpriteRef(), enemy.getPos(), enemy.getColor());
}

void Battle::updateState(Player &player, Foe &enemy, GameState &gameState, Camera2D &main) {
    Vector2 playerPos = { ScreenSettings::w / 4, ScreenSettings::centerY };
    Vector2 enemyPos =  { ScreenSettings::centerX, ScreenSettings::centerY };

    if (win) {
        _battleData.currentTurn = BattleTurn::UNDEFINED;
        main.zoom = 1;
        player.unlockRandomGear();
        player.setPos(playerPos);
        player.setCanMove(true);
        enemy.setPos(enemyPos);
        _battleData.battleFinished = true;
        if (_battleData.currentLevel < maxLevel) { ++_battleData.currentLevel; }
        gameState = EXPLORING;
    }
    else if (lose) {
        _battleData.currentTurn = BattleTurn::UNDEFINED;
        main.zoom = 1;
        player.setPos(playerPos);
        player.setCanMove(true);
        enemy.setPos(enemyPos);
        gameState = EXPLORING;
    }
}

bool Battle::handlePlayerAnimations(Player &player, InternalOption &internalOption, GameState &gameState) {
    if (gameState != INBATTLE) return false;

    Vector2 playerPos = { ScreenSettings::centerX / 4, ScreenSettings::centerY };

    switch (player.getCurrentWeapon()) {
        case CRIMSONKATANA:
            switch (internalOption) {
                case InternalOption::NONE: playerAnimations.CrimsonKatanaIdle(player.getSpriteRef(), playerPos); break;
                case InternalOption::BA: return playerAnimations.CrimsonKatanaBA(player.getSpriteRef(), playerPos);
                case InternalOption::EA: return playerAnimations.CrimsonKatanaEA(player.getSpriteRef(), playerPos);
                case InternalOption::BM: return playerAnimations.CrimsonKatanaBM(player.getSpriteRef(), playerPos);
                case InternalOption::EM: return playerAnimations.CrimsonKatanaEM(player.getSpriteRef(), playerPos);
            }
            break;
        case CELESTIALBOW:
            switch (internalOption) {
                case InternalOption::NONE: playerAnimations.CelestialBowIdle(player.getSpriteRef(), playerPos); break;
                case InternalOption::BA: return playerAnimations.CelestialBowBA(player.getSpriteRef(), playerPos);
                case InternalOption::EA: return playerAnimations.CelestialBowEA(player.getSpriteRef(), playerPos);
                case InternalOption::BM: return playerAnimations.CelestialBowBM(player.getSpriteRef(), playerPos);
                case InternalOption::EM: return playerAnimations.CelestialBowEM(player.getSpriteRef(), playerPos);
            }
            break;
    }
    return false;
}


void Battle::generateEnemyPattern() {
    enemyOption = rand() % (3 - 1) + 1;
}

bool Battle::handleEnemyAnimations(Foe &enemy, GameState &gameState) {
    if (gameState != INBATTLE) return false;

    auto &enemySprite = enemy.getSpriteRef();
    Vector2 enemyPos = enemy.getPos();
    Color enemyColor = enemy.getColor();

    if (enemyAnimating) {
        switch (enemyOption) {
            case 1: return foeAnimations.KBasicAttack(enemySprite, enemyPos, enemyColor);
            case 2: return foeAnimations.KBasicMagic(enemySprite, enemyPos, enemyColor);
        }
    }
    return false;
}


void Battle::handleBattleAnimations(ActionBox &actionBox, Player &player, Foe &enemy, GameState &gameState) {
    bool playerAnimFinished = handlePlayerAnimations(player, internalChoice, gameState);
    bool enemyAnimFinished = handleEnemyAnimations(enemy, gameState);

    Vector2 damageMarkPos = { .x = enemy.getPos().x, .y = enemy.getPos().y };

    if (playerAnimating) {
        actionBox.setCurrentOption(ActionOption::SELECTION);

        switch (internalChoice) {
            case InternalOption::BA:
            case InternalOption::EA:
                player.displayDamageMark(damageMarkPos, WHITE);
                break;
            case InternalOption::BM:
            case InternalOption::EM:
                player.displayDamageMark(damageMarkPos, PINK);
                break;
        }

        if (playerAnimFinished) {
            _battleData.currentTurn = BattleTurn::ENEMY;
            internalChoice = InternalOption::NONE;
            playerAnimating = false;
        }
        return;
    }

    if (enemyAnimating) {
        if (enemyAnimFinished) {
            _battleData.currentTurn = BattleTurn::PLAYER;
            enemyAnimating = false;
        }
        return;
    }
}

void Battle::manageInternalOption(ActionBox &actionBox, Vector2 &mousePos) {
    if (internalChoice == InternalOption::NONE && !playerAnimating) {
        internalChoice = actionBox.handleInternalOptions(mousePos);
        playerAnimating = false;
    }
}



void Battle::battleLoop(Player &player, Foe &enemy, GameState &gameState, Vector2 &mousePos) {
    if (gameState != INBATTLE) return;

    //player.update(player.getStat());
    //enemy.update(enemy.getStat());

    switch (_battleData.currentTurn) {
    case BattleTurn::UNDEFINED:
        _battleData.currentTurn = BattleTurn::ENEMY;
        break;
    case BattleTurn::PLAYER:
        if (!playerAnimating && internalChoice != InternalOption::NONE) {
            switch (internalChoice) {
                case InternalOption::BA:
                    player.dealDamage(enemy);
                    break;
                case InternalOption::EA:
                    player.dealDamageEnhanced(enemy);
                    break;
                case InternalOption::BM:
                    player.dealDamageMagic(player, enemy);
                    break;
                case InternalOption::EM:
                    player.dealDamageMagic(player, enemy);
                    break;
            }
            playerAnimating = true;
        }
        break;
    case BattleTurn::ENEMY:
        if (!enemyAnimating) {
            generateEnemyPattern();
            switch (enemyOption) {
                case 1:
                    enemy.dealDamage(player);
                    enemyAnimating = true;
                    break;
                case 2:
                    enemy.dealDamageMagic(enemy, player);
                    enemyAnimating = true;
                    break;
            }
        }
        break;
    }
}
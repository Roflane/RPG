#include "Player.h"

uint8 _ = 0;
static uint8 frameCounter = 0;
static uint8 frameDelay = 10;

Player::Player() : Entity(0, Vector2(0, 0), Stats(), Color()), MovementComponent(0), DamageComponent(Stats()),
    _baseStats(), _availableGear(), _currentGear(), _currentWeapon() {}


Player::Player(const char *spritePath, Vector2 pos, Stats stats, Color color, float moveSpeed) :
    Entity(spritePath, pos, stats, color), MovementComponent(moveSpeed), DamageComponent(stats) {
    _currentWeapon = CRIMSONKATANA;
    _availableGear.set(T3HEAD);
    _currentGear = { T3HEAD, NONEGEAR, NONEGEAR, NONEGEAR, NONEGEAR };
    _baseStats = stats;
}



void Player::drawShadows() {
    Color shadowColor = Fade(BLACK, 0.5f);
    uint8 offset = 2;

    switch (__dir) {
        case UP:
            DrawTexture(__sprite, __pos.x + offset, __pos.y + offset, shadowColor);
            break;
        case DOWN:
            DrawTexture(__sprite, __pos.x + offset, __pos.y - offset, shadowColor);
            break;
        case LEFT:
            DrawTexture(__sprite, __pos.x + offset, __pos.y + offset, shadowColor);
            break;
        case RIGHT:
            DrawTexture(__sprite, __pos.x - offset, __pos.y - offset, shadowColor);
            break;
    }
}


void Player::moveUp() {
    static uint8 idx = 0;
    AnimateSprite(__sprite, PlayerAssets::spritesUp, __pos, 2, frameDelay, idx, __color);
}
void Player::moveDown() {
    static uint8 idx = 0;
    AnimateSprite(__sprite, PlayerAssets::spritesDown, __pos, 2, frameDelay, idx, __color);
}
void Player::moveLeft() {
    static uint8 idx = 0;
    AnimateSprite(__sprite, PlayerAssets::spritesLeft, __pos, 12, 12, idx, __color);
}
void Player::moveRight() {
    static uint8 idx = 0;
    AnimateSprite(__sprite, PlayerAssets::spritesRight, __pos, 12, 12, idx, __color);
}

void Player::idle() {
    static uint8 idx = 0;
    AnimateSprite(__sprite, PlayerAssets::spritesIdle, __pos, 6, frameDelay * 3, idx, __color);
}

void Player::restrictMovement(uint16 mapW, uint16 mapH) {
    __pos.x = clamp<float>(__pos.x, 0, mapW - __sprite.width);
    __pos.y = clamp<float>(__pos.y, 0, mapH - __sprite.height);
}
void Player::move(float &dt) {
    if (__canMove) { MovementComponent::move(__pos.x, __pos.y, dt); }
}
void Player::draw() {
    switch (getDir()) {
        case UP:    moveUp();    break;
        case DOWN:  moveDown();  break;
        case LEFT:  moveLeft();  break;
        case RIGHT: moveRight(); break;
        case IDLE:  idle();  break;
    }
}

void Player::updateStats() {
    __stats = _baseStats;

    __stats.atk += weaponStats[_currentWeapon].atk;
    __stats.edb += weaponStats[_currentWeapon].edb;
    __stats.cr += weaponStats[_currentWeapon].cr;
    __stats.cd += weaponStats[_currentWeapon].cd;

    for (uint8 i = 0; i < _currentGear.size(); ++i) {
        if (_currentGear[i] != Gear::NONEGEAR) {
            __stats.hp += gearStats[_currentGear[i]].hp;
            __stats.atk += gearStats[_currentGear[i]].atk;
            __stats.def += gearStats[_currentGear[i]].def;
            __stats.edr += gearStats[_currentGear[i]].edr;
            __stats.cdr += gearStats[_currentGear[i]].cdr;
        }
    }

    getDamageComponentStats() = __stats;
}

void Player::unlockRandomGear() {
    std::vector<uint8> lockedIdx;

    for (uint8 i = 0; i < _availableGear.size(); ++i) {
        if (!_availableGear[i]) {
            lockedIdx.push_back(i);
        }
    }
    if (lockedIdx.empty()) return;

    uint8 randomIdx = GetRandomValue(0, lockedIdx.size() - 1);
    uint8 gearToUnlock = lockedIdx[randomIdx];

    _availableGear.set(gearToUnlock);
}
#pragma once
#include <vector>
#include <bitset>
#include "Entity.h"
#include "../assets/PlayerAssets.h"
#include "../components/MovementComponent.h"
#include "../components/DamageComponent.h"
#include "../animations/PlayerAnimations.h"
#include "../items/Weapon.h"
#include "../items/Gear.h"
#include "../stats/ItemStats.h"

class Player : public Entity, public MovementComponent, public DamageComponent {
private:
	Stats _baseStats;
	std::bitset<15> _availableGear;
	std::vector<Gear> _currentGear;
	Weapon _currentWeapon;
public:
	~Player() = default;
	Player();
	Player(const char *spritePath, Vector2 pos, Stats stats, Color color, float moveSpeed);

	// Properties
	Weapon& getCurrentWeapon()					  { return _currentWeapon;  }

	std::bitset<15> getAvailableGear() const	  { return _availableGear; }

	std::vector<Gear>& getCurrentGear()			  { return _currentGear; }
	void setCurrentGear(uint8 index, Gear gear)   { _currentGear[index] = gear; }


	// Methods
	void drawShadows() override;
	void draw() override;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void idle();
	void move(float &dt);
	void restrictMovement(uint16 mapW, uint16 mapH);

	void updateStats();
	void unlockRandomGear();
};
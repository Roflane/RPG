#pragma once
#include "../stats/Stats.h"
#include "../../base/misc.h"

class Entity {
protected:
	Texture2D __sprite;
	Vector2 __pos;
	Stats __stats;
	Color __color;
public:
	Entity(const char *path, Vector2 pos, Stats stats, Color color) : __sprite(LoadTexture(path)), __pos(pos), __stats(stats), __color(color) {}
	~Entity() { UnloadTexture(__sprite); }

	// Properties
	Texture2D& getSpriteRef()    { return __sprite; }
	Texture2D getSprite() const	 { return __sprite; }

	void setPos(Vector2 pos)     { __pos = pos; }
	Vector2 getPos() const		 { return __pos; }
	Rectangle getRect() const	 { return Rectangle(__pos.x, __pos.y, __sprite.width, __sprite.height); }
	
	Stats& getStatRef()			{ return __stats;  }
	Stats getStat() const		{ return __stats; }
	void setStats(Stats stats)  { __stats = stats; }

	Color getColor() const		{ return __color; }
	void setColor(Color value)  { __color = value; }

	// Methods
	void decreaseHp(decltype(__stats.hp) value)	   { __stats.hp -= value; }
	void decreaseMana(decltype(__stats.mana) value) { __stats.mana -= value; }
		 
	virtual void drawShadows() = 0;
	virtual void draw() = 0;
};
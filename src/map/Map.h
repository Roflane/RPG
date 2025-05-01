#pragma once
#include <raylib.h>
#include "../../base/typedefs.h"

class Map {
private:
	Texture2D _map;
	Vector2 _pos;
	Color _color;
public:
	Map() : _map(), _pos(), _color() {}
	Map(const char* mapPath, Vector2 pos, Color color) : _map(LoadTexture(mapPath)), _pos(pos), _color(color) {}

	// Properties
	Vector2 getPos() const		{ return _pos; }

	float getW() const			{ return _map.width; }
	float getH() const		    { return _map.height; }

	float getMapCenterX() const { return _map.width / 2; }
	float getMapCenterY() const { return _map.height / 2; }

	Color getColor() const		{ return _color; }
	void setColor(Color value)  { _color = value; }

	// Methods
    void render();
};
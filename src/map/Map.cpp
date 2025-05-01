#include "Map.h"

void Map::render() {
	DrawTexture(_map, _pos.x, _pos.y, _color);
}
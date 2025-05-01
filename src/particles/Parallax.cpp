#include "Parallax.h"

void Parallax::Update(float dt) {
	for (uint16 i = 0; i < _particles.size(); i++) {
		_particles[i].x -= _scrollSpeed * (_particles[i].z / 1);

		if (_particles[i].x <= 0) {
			_particles[i].x += GetRandomValue(0, ScreenSettings::w);
			_particles[i].y = GetRandomValue(0, ScreenSettings::h);
		}
	}
}

void Parallax::Draw() {
	for (uint16 i = 0; i < _particles.size(); i++) {
		float x = _particles[i].x;
		float y = _particles[i].y;
		DrawPixel(x, y, WHITE);
	}
}

#pragma once
#include "../../base/misc.h"
#include "../settings/GlobalSettings.h"

struct Particle { float x, y, z; };

class Parallax {
private:
    uint16 _scrollSpeed;
    Color _color;
    std::vector<Particle> _particles;
public:
    Parallax() : _color(), _scrollSpeed(), _particles() {}
    Parallax(uint16 count, uint16 scrollSpeed, Color color)
        : _scrollSpeed(scrollSpeed), _color(color), _particles(count) {
        for (int i = 0; i < _particles.size(); i++) {
            _particles[i].x = GetRandomValue(0, ScreenSettings::w);
            _particles[i].y = GetRandomValue(0, ScreenSettings::h);
            _particles[i].z = GetRandomValueFloat(0, 1000.f);
        }
    }

    void Draw();
    void Update(float dt);
};
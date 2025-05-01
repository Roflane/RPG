#pragma once
#include "Stats.h"

namespace IPS {
    inline decltype(Stats{}.mana) mana = 100;
    inline decltype(Stats{}.hp)   hp = 100;
    inline decltype(Stats{}.atk)  atk = 7;
    inline decltype(Stats{}.def)  def = 15;
    inline decltype(Stats{}.edb)  edb = 2;
    inline decltype(Stats{}.edr)  edr = 3;
    inline decltype(Stats{}.cr)   cr = 50.f;
    inline decltype(Stats{}.cd)   cd = 40;
    inline decltype(Stats{}.cdr)  cdr = 20;
}

namespace IES {
    inline decltype(Stats{}.mana) mana = 100;
    inline decltype(Stats{}.hp)   hp = 100;
    inline decltype(Stats{}.atk)  atk = 25;
    inline decltype(Stats{}.def)  def = 15;
    inline decltype(Stats{}.edb)  edb = 23;
    inline decltype(Stats{}.edr)  edr = 3;
    inline decltype(Stats{}.cr)   cr = 20.f;
    inline decltype(Stats{}.cd)   cd = 40;
    inline decltype(Stats{}.cdr)  cdr = 20;
}


namespace EnemyStats {
    inline Stats first = {
        IES::mana, IES::hp, IES::atk, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats second = {
        IES::mana, IES::hp + 10, IES::atk + 15, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats third = {
        IES::mana, IES::hp + 50, IES::atk + 25, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats fourth = {
        IES::mana, IES::hp + 100, IES::atk + 35, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats fifth = {
        IES::mana, IES::hp + 150, IES::atk + 45, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats sixth = {
        IES::mana, IES::hp + 200, IES::atk + 55, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats seventh = {
        IES::mana, IES::hp + 300, IES::atk + 65, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats eighth = {
        IES::mana, IES::hp + 400, IES::atk + 75, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats ninth = {
        IES::mana, IES::hp + 500, IES::atk + 85, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };

    inline Stats tenth = {
        IES::mana, IES::hp + 600, IES::atk + 95, IES::def,
        IES::edb, IES::edr,
        IES::cr, IES::cd, IES::cdr
    };
}


struct InitEntityData {
    decltype(Stats{}.hp) playerHP = 0, enemyHP = 0;
    decltype(Stats{}.mana) playerMANA = 100, enemyMANA = 100;
};
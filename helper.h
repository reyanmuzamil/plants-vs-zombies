#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <cstdint>

constexpr int GRID_ROWS = 5;
constexpr int GRID_COLS = 9;

enum PlantType : uint8_t {
    PLANT_NONE        = 0,
    PLANT_SUNFLOWER   = 1,
    PLANT_PEASHOOTER  = 2,
    PLANT_WALLNUT     = 3,
    PLANT_SNOW_PEA    = 4,
    PLANT_REPEATER    = 5,
    PLANT_POTATO_MINE = 6,
    PLANT_CHERRY_BOMB = 7
};

enum ZombieType : uint8_t {
    ZOMBIE_REGULAR        = 1,
    ZOMBIE_CONEHEAD       = 2,
    ZOMBIE_BUCKETHEAD     = 3,
    ZOMBIE_NEWSPAPER      = 4,
    ZOMBIE_POLE_VAULTER   = 5,
    ZOMBIE_SMART_SWITCHER = 6, // Uses BFS when blocked
    ZOMBIE_GARGANTUAR     = 7
};

enum ProjectileType : uint8_t {
    PROJ_PEA        = 1,
    PROJ_FROZEN_PEA = 2
};

enum MatchStatus : uint8_t {
    STATUS_ACTIVE      = 1,
    STATUS_PAUSED      = 2,
    STATUS_PLANTS_WIN  = 3,
    STATUS_ZOMBIES_WIN = 4
};

#pragma pack(push, 1)
struct Tile {
    uint8_t plant_type;
    int16_t hp;
    int16_t cooldown;   // For Potato Mine: >0 means still arming, 0 means armed & ready
};

struct Zombie {
    int32_t id;
    uint8_t type;
    uint8_t row;
    float x;            // 0.0 (House) to 8.9 (Right spawn edge)
    int16_t hp;
    float speed;        // Base tiles moved per tick
    int16_t damage;     // Damage per tick when attacking
    uint8_t slow_ticks; // Remaining ticks slowed by Snow Pea (0 = normal speed)
    bool used_bfs;      // Smart Switcher flag
    bool has_vaulted;   // Pole Vaulter flag
};

struct Projectile {
    int32_t id;
    uint8_t type;       // PROJ_PEA or PROJ_FROZEN_PEA
    uint8_t row;
    float x;
    float speed;
    int16_t damage;
};

struct PlantMove {
    uint8_t row;
    uint8_t col;
    uint8_t plant_type;
    int32_t sun_refund;
};
#pragma pack(pop)

inline int getPlantCost(PlantType type) {
    switch (type) {
        case PLANT_SUNFLOWER:   return 50;
        case PLANT_PEASHOOTER:  return 100;
        case PLANT_WALLNUT:     return 50;
        case PLANT_SNOW_PEA:    return 175;
        case PLANT_REPEATER:    return 200;
        case PLANT_POTATO_MINE: return 25;
        case PLANT_CHERRY_BOMB: return 150;
        default:                return 0;
    }
}

inline int getZombieCost(ZombieType type) {
    switch (type) {
        case ZOMBIE_REGULAR:        return 50;
        case ZOMBIE_CONEHEAD:       return 75;
        case ZOMBIE_BUCKETHEAD:     return 125;
        case ZOMBIE_NEWSPAPER:      return 100;
        case ZOMBIE_POLE_VAULTER:   return 100;
        case ZOMBIE_SMART_SWITCHER: return 100;
        case ZOMBIE_GARGANTUAR:     return 250;
        default:                    return 0;
    }
}

#endif
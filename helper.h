#ifndef GAME_TYPES_H
#define GAME_TYPES_H
#include <cstdint>
constexpr int GRID_ROWS = 5;
constexpr int GRID_COLS = 9;

enum PlantType : uint8_t {
    PLANT_NONE = 0,
    PLANT_SUNFLOWER = 1,
    PLANT_PEASHOOTER = 2,
    PLANT_WALLNUT = 3,
    PLANT_CHERRY_BOMB = 4
};

enum ZombieType : uint8_t {
    ZOMBIE_REGULAR = 1,
    ZOMBIE_CONEHEAD = 2,
    ZOMBIE_BUCKETHEAD = 3,
    ZOMBIE_SMART_SWITCHER = 4 // Uses BFS when blocked
};

enum MatchStatus : uint8_t {
    STATUS_ACTIVE = 1,
    STATUS_PAUSED = 2,
    STATUS_PLANTS_WIN = 3,
    STATUS_ZOMBIES_WIN = 4
};

#pragma pack(push, 1)
struct Tile {
    uint8_t plant_type;
    int16_t hp;
    int16_t cooldown; // Ticks remaining until next action/detonation
};

struct Zombie {
    int32_t id;
    uint8_t type;
    uint8_t row;
    float x;          // 0.0 (House) to 8.9 (Right spawn edge)
    int16_t hp;
    float speed;      // Tiles moved per tick
    int16_t damage;   // Damage per tick when eating a plant
    bool used_bfs;    // Prevents infinite lane-bouncing
};

struct Projectile {
    int32_t id;
    uint8_t row;
    float x;          // Moves left-to-right
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
        case PLANT_CHERRY_BOMB: return 150;
        default:                return 0;
    }
}

inline int getZombieCost(ZombieType type) {
    switch (type) {
        case ZOMBIE_REGULAR:        return 50;
        case ZOMBIE_CONEHEAD:       return 75;
        case ZOMBIE_BUCKETHEAD:     return 125;
        case ZOMBIE_SMART_SWITCHER: return 100;
        default:                    return 0;
    }
}

#endif
#pragma once
#include "stack.h"
#include "doubly_linkedlist.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "helper.h"
class GameEngine {
    public:
    int32_t room_id;
    uint8_t status;
    int32_t tick_count;
    int32_t sun; // currency for plants
    int32_t brains; // currency for zombies
    int32_t next_entity_id;
    //5x9 2D Array
    Tile grid[GRID_ROWS][GRID_COLS];
    bool has_lawnmower[GRID_ROWS];
    // Doubly Linked Lists per lane
    DoublyLinkedList<Zombie> zombieLanes[GRID_ROWS];
    DoublyLinkedList<Projectile> peaLanes[GRID_ROWS];
    // Undo Stack
    Stack<PlantMove> moveStack;

    GameEngine(int32_t id = 1, int32_t startSun = 250, int32_t startBrains = 250)
        : room_id(id), status(STATUS_ACTIVE), tick_count(0),
          sun(startSun), brains(startBrains), next_entity_id(1) {
        for (int r = 0; r < GRID_ROWS; r++) {
            has_lawnmower[r] = true;
            for (int c = 0; c < GRID_COLS; c++) {
                grid[r][c] = { PLANT_NONE, 0, 0 };
            }
        }
    }
    void placeplant(int r, int c, PlantType plant_type){
        if(status != STATUS_ACTIVE) return;
        if(r >= GRID_ROWS || c >= GRID_COLS || r < 0 || c < 0) return;
        if(grid[r][c].plant_type != PLANT_NONE) return;
        if(sun>=getPlantCost(plant_type)){
            sun -= getPlantCost(plant_type);
            grid[r][c].plant_type = plant_type;
            switch (plant_type)
            {
            case PLANT_SUNFLOWER:
                grid[r][c].hp = 100;
                grid[r][c].cooldown = 0;
                break;
            case PLANT_PEASHOOTER:
                grid[r][c].hp = 100;
                grid[r][c].cooldown = 0;
                break;
            case PLANT_WALLNUT:
                grid[r][c].hp = 1000;
                grid[r][c].cooldown = 0;
                break;
            case PLANT_SNOW_PEA:
                grid[r][c].hp = 100;
                grid[r][c].cooldown = 0;
                break;
            case PLANT_REPEATER:
                grid[r][c].hp = 100;
                grid[r][c].cooldown = 0;
                break;
            case PLANT_POTATO_MINE:
                grid[r][c].hp = 100;
                grid[r][c].cooldown = 15; // Assuming 15 ticks for arming
                break;
            case PLANT_CHERRY_BOMB:
                grid[r][c].hp = 100;
                grid[r][c].cooldown = 0;
                break;
            default:
                break;
           } 
            moveStack.push({(uint8_t)r, (uint8_t)c, (uint8_t)plant_type, 0}); // for undo functionality, sun_refund is set to 0 for now
        }
    }
    void undoLastMove(){
        if(status != STATUS_ACTIVE) return;
        PlantMove lastMove;
        if(moveStack.pop(lastMove)){
            int r = lastMove.row;
            int c = lastMove.col;
            PlantType plant_type = (PlantType)lastMove.plant_type;
            if(r < GRID_ROWS && c < GRID_COLS && r >= 0 && c >= 0){
                sun += getPlantCost(plant_type);
                grid[r][c].plant_type = PLANT_NONE;
                grid[r][c].hp = 0;
                grid[r][c].cooldown = 0;
            }
        }
    }
    void spawnZombie(int r, ZombieType zombie){
        if(status != STATUS_ACTIVE) return;
        if(r >= GRID_ROWS || r < 0) return;
        int32_t id = next_entity_id++;
        if(brains>=getZombieCost(zombie)){
            brains -= getZombieCost(zombie);
        Zombie z{};
        z.id = next_entity_id++;
        z.type = zombie;
        z.row = static_cast<uint8_t>(r);
        z.x = 8.8f;
        z.used_bfs = false;
        z.has_vaulted = false;
        switch (zombie){
            case ZOMBIE_REGULAR:
                z.hp = 100;
                z.speed = 0.1f;
                z.damage = 10;
                z.slow_ticks = 0;
                break;
            case ZOMBIE_CONEHEAD:
                z.hp = 200;
                z.speed = 0.1f;
                z.damage = 10;
                z.slow_ticks = 0;
                break;
            case ZOMBIE_BUCKETHEAD:
                z.hp = 300;
                z.speed = 0.1f;
                z.damage = 10;
                z.slow_ticks = 0;
                break;
            case ZOMBIE_NEWSPAPER:
                z.hp = 150;
                z.speed = 0.1f;
                z.damage = 10;
                z.slow_ticks = 0;
                break;

            case ZOMBIE_POLE_VAULTER:
                z.hp = 100;
                z.speed = 0.1f;
                z.damage = 10;
                z.slow_ticks = 0;
                break;
            case ZOMBIE_SMART_SWITCHER:
                z.hp = 100;
                z.speed = 0.1f;
                z.damage = 10;
                z.slow_ticks = 0;
                break;
            case ZOMBIE_GARGANTUAR:
                z.hp = 500;
                z.speed = 0.1f;
                z.damage = 20;
                z.slow_ticks = 0;
                break;
            default:
                return;
        }
        zombieLanes[r].pushBack(z);
        }
    }
};
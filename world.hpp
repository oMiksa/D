#ifndef WORLD_HPP
#define WORLD_HPP
#include "bot.hpp"
#include <stdio.h>

#define worldX 64
#define worldY 32

#define EMPTY 0
#define BOT 1
#define FOOD 2
#define POISON 3
#define WALL 4

class world {
private:
    // int countBot;
    // int countFood;
    // int countPoison;
    // int countWall;
    bot W[worldX][worldY];
    
public:
    int countBot;
    int countFood;
    int countPoison;
    int countWall;
    void run();
    void swap(bot*a, bot*b);
    int move(bot* b);
    int take(bot* b);
    bot* see(bot* b, int f = 0);
    bot getElem(int x, int y);
    world(int b, int f, int p, int w);
    ~world();
};

#endif
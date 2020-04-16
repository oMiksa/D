#ifndef WORLD_HPP
#define WORLD_HPP
#include "element.hpp"
#include <stdio.h>

#define worldX 64
#define worldY 32

struct cord {
    bool fail;
    int x;
    int y;
};


class world {
private:
    element W[worldX][worldY];
    element W2[10];
    
public:
    int countBot;
    int countFood;
    int countPoison;
    int countWall;
    void run();
    void newGenerration();
    void legacy();
    void swap(cord a, cord b);
    cord see(cord b, int focus, int cmd = 0);
    element getElem(int x, int y);
    world(int b, int f, int p, int w);
    void init(int b, int f, int p, int w);
    world(int);
    ~world();
};

#endif
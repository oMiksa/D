#include "world.hpp"

void world::newGenerration() {
    bool mutation = true;
    int k = 0;
    for (int i = 0; i < worldX; i++) {
        for (int j = 0; j < worldY; j++) {
            if (W[i][j].getStatus() == BOT && k < 10) {
                for(int q = 0; q < MAX_CMD; q++) {
                    W2[k].setCMD(q,W[i][j].getCMD(q));
                }
                k++;
            }
        }
    }
    if (mutation)
        W2[rand() % k].setCMD(rand() % MAX_CMD, rand() % 32);
    // for (int i = 0; i < 10; i++) {
        // for (int j = 0; j < MAX_CMD; j++) {
            // printf("%d) %d, ", i, W2[i].getCMD(j));
        // }
        // printf("\n");
    // }
}    

void world::legacy() {
    int count = 0;
    int k = 0;
    for (int i = 0; i < worldX; i++) {
        for (int j = 0; j < worldY; j++) {
            if (W[i][j].getStatus() == BOT) {
                printf("%d", k);
                for (int q = 0;  q < MAX_CMD; q++) {
                    W[i][j].setCMD(q, W2[k].getCMD(q));
                    printf("%d,", W2[k].getCMD(q));
                }
                printf("\n");
                count++;
                if (count == 8) {
                    k++;
                    count = 0;
                }
            }   
        }
    }
}

cord world::see(cord b, int f, int cmd) {
    bool banJumpX = false;
    bool banJumpY = true;
    bool failJump = false;
    float x = (float)b.x;
    float y = (float)b.y;
    switch ( (f + cmd) % 8) {
        case 0:
            if ( ((float)b.y - 1.0f) < 0.0f) {
                y = ((float)worldY - 1.0f);
                failJump += banJumpY;
            } else 
                y = ((float)b.y - 1.0f);
            break;
        case 1:
            if ( ((float)b.x + 1.0f) >= (float)worldX) {
                x = (0.0f);
                failJump += banJumpX;
            } else
                x = ((float)b.x + 1.0f);
            ////////////////////////
            if ( ((float)b.y - 1.0f) < 0.0f) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = ((float)b.y - 1.0f);
            break;
        case 2:
            if ( ((float)b.x + 1.0f) >= (float)worldX) {
                x = (0.0f);
                failJump += banJumpX;
            } else
                x = ((float)b.x + 1.0f);
            break;
        case 3:
            if ( ((float)b.x + 1.0f) >= (float)worldX) {
                x = (0.0f);
                failJump += banJumpX;
            } else
                x = ((float)b.x + 1.0f);
            /////////////////////////////////////
            if ( ((float)b.y + 1.0f) >= (float)worldY) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = ((float)b.y + 1.0f);            
            break;
        case 4:
            if ( ((float)b.y + 1.0f) >= (float)worldY) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = ((float)b.y + 1.0f);            
            break;
        case 5:
            if ( ((float)b.x - 1.0f) < 0.0f) {
                x = ((float)worldX - 1.0f);
                failJump += banJumpX;
            } else
                x = ((float)b.x - 1.0f);
            //////////////
            if ( ((float)b.y + 1.0f) >= (float)worldY) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = ((float)b.y + 1.0f);            
            break;
        case 6:
            if ( ((float)b.x - 1.0f) < 0.0f) {
                x = ((float)worldX - 1.0f);
                failJump += banJumpX;
            } else
                x = ((float)b.x - 1.0f);
            
            break;
        case 7:
            if ( ((float)b.x - 1.0f) < 0.0f) {
                x = ((float)worldX - 1.0f);
                failJump += banJumpX;
            } else
                x = ((float)b.x - 1.0f);
            /////////////
            if ( ((float)b.y - 1.0f) < 0.0f) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = ((float)b.y - 1.0f);

            break;
    }
    //printf("(%f, %f)see(%f, %f) = %d(%d)\n", (float)b.x, (float)b.y, x, y, W[(int)x][(int)y].getStatus(), failJump);
    cord r;
    r.x = (int)x;
    r.y = (int)y;
    r.fail = failJump;
    return r;
}

void world::swap(cord a, cord b) {
    //printf("(%d, %d) - >", W[a.x][a.y].getStatus(),W[b.x][b.y].getStatus());
    element t = W[a.x][a.y];
    W[a.x][a.y] = W[b.x][b.y];
    W[b.x][b.y] = t;
    //printf("(%d, %d)\n", W[a.x][a.y].getStatus(),W[b.x][b.y].getStatus());
}

void world::run() {
    //printf("run\n");
    countBot = 0;
    countFood = 0;
    countPoison = 0;
    countWall = 0;
    for (int i = 0; i < worldX; i++)
        for (int j = 0; j < worldY; j++) {
            W[i][j].actionON();
            switch (W[i][j].getStatus()) {
                case EMPTY:break;
                case BOT: 
                    countBot++; 
                    //printf("%d)(%d,%d)\n", countBot, i, j); 
                    break;
                case FOOD: countFood++; break;
                case POISON: countPoison++; break;
                case WALL: countWall++; break;
            }
            
        }

    element *elm;
    int cmd, countCMD;
    cord corElm, corFocus;
    bool runCMD;
    for (int i = 0; i < worldX; i++)
        for (int j = 0; j < worldY; j++) {
            /////////////////////////
            corElm.x = i;
            corElm.y = j;
            elm = &W[corElm.x][corElm.y];
            /////////////////////////
            if (elm->getStatus() == BOT) {
                runCMD = elm->isAction();
                countCMD = 0;
                while (runCMD) {            
                    cmd = elm->getCMD();
                    //printf("(%d, %d)%d - (%f, %f)\n", i, j, pB->getCMD(), pB->getPosX(), pB->getPosY());
                    if (0 <= cmd && cmd <= 7) {
                        //move
                        runCMD = false;
                        corFocus = see(corElm, elm->getFocus(), cmd);
                        //printf("%d - %d = %d\n", corElm.x, corElm.y, W[corElm.x][corElm.y].getStatus());
                        //printf("%d - %d = %d\n", corFocus.x, corFocus.y, W[corFocus.x][corFocus.y].getStatus());
                        if(!corFocus.fail) {
                            switch (getElem(corFocus.x, corFocus.y).getStatus()) {
                                case EMPTY:
                                    elm->indexUp(EMPTY + 1);
                                    swap(corElm, corFocus);
                                    elm = &W[corFocus.x][corFocus.y];
                                    break;
                                case BOT:
                                    elm->indexUp(BOT + 1);
                                    break;
                                case FOOD:
                                    elm->indexUp(FOOD + 1);
                                    elm->upLife(10);
                                    W[corFocus.x][corFocus.y].setStatus(EMPTY);
                                    swap(corElm, corFocus);
                                    elm = &W[corFocus.x][corFocus.y];
                                    countFood--;
                                    break;
                                case POISON:
                                    elm->indexUp(POISON + 1);
                                    countPoison--;
                                    countBot--;
                                    W[corFocus.x][corFocus.y].setStatus(EMPTY);
                                    swap(corElm, corFocus);
                                    elm = &W[corFocus.x][corFocus.y];
                                    elm->setStatus(FOOD);
                                    break;
                                case WALL:
                                    elm->indexUp(WALL + 1);
                                    break;
                            }
                        }
                    }

                    if (8 <= cmd && cmd <= 15) {
                        //take
                        runCMD = false;
                        corFocus = see(corElm, elm->getFocus(), cmd - 8);
                        if(!corFocus.fail) {
                            switch (getElem(corFocus.x, corFocus.y).getStatus()) {
                                case EMPTY:
                                    elm->indexUp(EMPTY + 1);
                                    break;
                                case BOT:
                                    elm->indexUp(BOT + 1);
                                    break;
                                case FOOD:
                                    elm->indexUp(FOOD + 1);
                                    countFood--;
                                    elm->upLife(10);
                                    W[corFocus.x][corFocus.y].setStatus(EMPTY);
                                    break;
                                case POISON:
                                    elm->indexUp(POISON + 1);
                                    elm->setStatus(FOOD);
                                    countPoison--;
                                    countFood++;
                                    break;
                                case WALL:
                                    elm->indexUp(WALL + 1);
                                    break;
                            }
                        }
                    }

                    if (16 <= cmd && cmd <= 23) {
                        //see
                        runCMD = false;
                        corFocus = see(corElm, elm->getFocus(), cmd - 16);
                        if(!corFocus.fail) {
                            switch (getElem(corFocus.x, corFocus.y).getStatus()) {
                                case EMPTY:
                                    elm->indexUp(EMPTY + 1);
                                    break;
                                case BOT:
                                    elm->indexUp(BOT + 1);
                                    break;
                                case FOOD:
                                    elm->indexUp(FOOD + 1);
                                    break;
                                case POISON:
                                    elm->indexUp(POISON + 1);
                                    W[corFocus.x][corFocus.y].setStatus(FOOD);
                                    countPoison--;
                                    countFood++;
                                    break;
                                case WALL:
                                    elm->indexUp(WALL + 1);
                                    break;
                            }
                        }
                    }

                    if (24 <= cmd && cmd <= 31) {
                        //turn
                        (countCMD >= 10) ? (runCMD = false) : countCMD++;
                        elm->indexUp(cmd);
                        elm->setFocus((elm->getFocus() + cmd - 24) % 8);
                    }

                    if (32 <= cmd && cmd <= 64) {
                        //miss
                        (countCMD >= 10) ? (runCMD = false) : countCMD++;
                        elm->indexUp(cmd);
                    }
                }
                if (elm->getStatus() == BOT) {
                    elm->actionOFF();
                    elm->upLife(-1);
                    //printf("(%d, %d) = %d(%d)\n", i, j, elm->getStatus(), elm->getLife());
                    if (!elm->isLife()){
                        elm->setStatus(FOOD);
                        countBot--;
                        countFood++;
                    }
                }
            }
        }
}

element world::getElem(int x, int y) {
    return W[x][y];
}
world::world(int a){
    countBot = 0;
    countFood = 0;
    countPoison = 0;
    countWall = 0;
for (int i = 0; i < worldX; i++)
    for (int j = 0; j < worldY; j++) {
        if (i == 32 && j == 15 || i == 10 && j == 10) {
            W[i][j].setStatus(BOT);
            W[i][j].genCDM(0, 7);
        } else {
            W[i][j].setStatus(FOOD);
        }
    }
}

world::world(int bot, int food, int poison, int wall) {
    init(bot, food, poison, wall);
}

void world::init(int bot, int food, int poison, int wall) {
    srand(time(0));
    countBot = 0;
    countFood = 0;
    countPoison = 0;
    countWall = 0;

    for (int i = 0; i < worldX; i++)
        for (int j = 0; j < worldY; j++)
            W[i][j].setStatus(EMPTY);

    int x, y;
    srand(time(NULL) + bot);
    while (countBot != bot) {
        x = rand() % worldX;
        y = rand() % worldY;
        //printf("bot - %d - %d(%d,%d)\n", countBot, bot, x, y);
        if (W[x][y].getStatus() == EMPTY) {
            W[x][y].setStatus(BOT);
                W[x][y].setStatus(BOT);
                W[x][y].genCDM(x * y * worldX);
                W[x][y].setLife(90);
                countBot++;
        }
    }

    srand(time(NULL) + food);
    while (countFood != food) {
        x = rand() % worldX;
        y = rand() % worldY;
        //printf("food - %d - %d(%d,%d)\n", countFood, food, x, y);
        if (W[x][y].getStatus() == EMPTY) {
            W[x][y].setStatus(FOOD);
            countFood++;
        }
    }

    srand(time(NULL) + poison);
    while (countPoison != poison) {
        x = rand() % worldX;
        y = rand() % worldY;
        //printf("poison - %d - %d(%d,%d)\n", countPoison, poison, x, y);
        if (W[x][y].getStatus() == EMPTY) {
            W[x][y].setStatus(POISON);
            countPoison++;
        }
    }

    srand(time(NULL) + wall);
    while (countWall != wall) {
        x = rand() % worldX;
        y = rand() % worldY;
        //printf("wall - %d - %d(%d,%d)\n", countWall, wall, x, y);
        if (W[x][y].getStatus() == EMPTY) {
            W[x][y].setStatus(WALL);
            countWall++;
        }
    }
}


world::~world() {
}

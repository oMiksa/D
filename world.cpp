#include "world.hpp"

int move(bot* b) {
    switch (b->getFocus()) {
        case 0:
            if ( (b->getPosY() + 1.0) > (float)worldY )
                b->setPosY(0.0f);
            else 
                b->setPosY(b->getPosY() + 1.0);
            break;
        case 1:
            if ( (b->getPosY() + 1.0) > (float)worldY )
                b->setPosY(0.0f);
            else 
                b->setPosY(b->getPosY() + 1.0);
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            /* code */
            break;
        case 6:
            /* code */
            break;
        case 7:

            break;
        default:
            return -1;
            break;
    }
}

int take(bot* b) {
    
}

bot* world::see(bot* b, int f) {
    bool banJumpX = false;
    bool banJumpY = true;
    bool failJump = false;
    float x = b->getPosX();
    float y = b->getPosY();
    switch ( (b->getFocus() + f) % 8) {
        case 0:
            if ( (b->getPosY() - 1.0f) < 0.0f) {
                y = ((float)worldY - 1.0f);
                failJump += banJumpY;
            } else 
                y = (b->getPosY() - 1.0f);
            break;
        case 1:
            if ( (b->getPosX() + 1.0f) >= (float)worldX) {
                x = (0.0f);
                failJump += banJumpX;
            } else
                x = (b->getPosX() + 1.0f);
            ////////////////////////
            if ( (b->getPosY() - 1.0f) < 0.0f) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = (b->getPosY() - 1.0f);
            break;
        case 2:
            if ( (b->getPosX() + 1.0f) >= (float)worldX) {
                x = (0.0f);
                failJump += banJumpX;
            } else
                x = (b->getPosX() + 1.0f);
            break;
        case 3:
            if ( (b->getPosX() + 1.0f) >= (float)worldX) {
                x = (0.0f);
                failJump += banJumpX;
            } else
                x = (b->getPosX() + 1.0f);
            /////////////////////////////////////
            if ( (b->getPosY() + 1.0f) >= (float)worldY) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = (b->getPosY() + 1.0f);            
            break;
        case 4:
            if ( (b->getPosY() + 1.0f) >= (float)worldY) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = (b->getPosY() + 1.0f);            
            break;
        case 5:
            if ( (b->getPosX() - 1.0f) < 0.0f) {
                x = ((float)worldX - 1.0f);
                failJump += banJumpX;
            } else
                x = (b->getPosX() - 1.0f);
            //////////////
            if ( (b->getPosY() + 1.0f) >= (float)worldY) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = (b->getPosY() + 1.0f);            
            break;
        case 6:
            if ( (b->getPosX() - 1.0f) < 0.0f) {
                x = ((float)worldX - 1.0f);
                failJump += banJumpX;
            } else
                x = (b->getPosX() - 1.0f);
            
            break;
        case 7:
            if ( (b->getPosX() - 1.0f) < 0.0f) {
                x = ((float)worldX - 1.0f);
                failJump += banJumpX;
            } else
                x = (b->getPosX() - 1.0f);
            /////////////
            if ( (b->getPosY() - 1.0f) < 0.0f) {
                y = (0.0f);
                failJump += banJumpY;
            } else
                y = (b->getPosY() - 1.0f);

            break;
    }
    return &W[(int)x][(int)y];
}

void world::swap(bot *a, bot *b) {
    bot *temp = a;
    a = b;
    b = temp;

    float tempX = a->getPosX();
    float tempY = a->getPosY();
    a->setPosX(b->getPosX());
    a->setPosY(b->getPosY());
    b->setPosX(tempX);
    b->setPosY(tempY);
}

void world::run() {
    printf("run (%d, %d)\n", countBot, countFood);
    bot *pB, *fB;
    int cmd, count;
    bool runBot;
    for (int i = 0; i < worldX; i++)
        for (int j = 0; j < worldY; j++) {
            pB = &W[i][j];
            if (pB->getStatus() == BOT) {
                runBot = true;
                count = 0;
                while (runBot) {            
                    cmd = pB->getCMD();
                    //printf("(%d, %d)%d - (%f, %f)\n", i, j, pB->getCMD(), pB->getPosX(), pB->getPosY());
                    if (0 <= cmd && cmd <= 7) {
                        //move
                        runBot = false;
                        fB = see(pB, cmd);
                        switch (fB->getStatus()) {
                            case EMPTY:
                                pB->indexUp(EMPTY + 1);
                                swap(fB, pB);
                                break;
                            case BOT:
                                pB->indexUp(BOT + 1);
                                break;
                            case FOOD:
                                pB->indexUp(FOOD + 1);
                                pB->upLife(10);
                                fB->setStatus(EMPTY);
                                swap(fB, pB);
                                countFood--;
                                break;
                            case POISON:
                                pB->indexUp(POISON + 1);
                                countPoison--;
                                countBot--;
                                fB->setStatus(EMPTY);
                                swap(fB, pB);
                                pB->setStatus(FOOD);
                                break;
                            case WALL:
                                pB->indexUp(WALL + 1);
                                break;
                        }
                    }

                    if (8 <= cmd && cmd <= 15) {
                        //take
                        runBot = false;
                        fB = see(pB, cmd - 8);
                        switch (fB->getStatus()) {
                            case EMPTY:
                                pB->indexUp(EMPTY + 1);
                                break;
                            case BOT:
                                pB->indexUp(BOT + 1);
                                break;
                            case FOOD:
                                pB->indexUp(FOOD + 1);
                                countFood--;
                                pB->upLife(10);
                                fB->setStatus(EMPTY);
                                break;
                            case POISON:
                                pB->indexUp(POISON + 1);
                                fB->setStatus(FOOD);
                                countPoison--;
                                countFood++;
                                break;
                            case WALL:
                                pB->indexUp(WALL + 1);
                                break;
                        }

                    }

                    if (16 <= cmd && cmd <= 23) {
                        //see
                        runBot = false;
                        fB = see(pB, cmd - 16);
                        switch (fB->getStatus()) {
                            case EMPTY:
                                pB->indexUp(EMPTY + 1);
                                break;
                            case BOT:
                                pB->indexUp(BOT + 1);
                                break;
                            case FOOD:
                                pB->indexUp(FOOD + 1);
                                break;
                            case POISON:
                                pB->indexUp(POISON + 1);
                                fB->setStatus(FOOD);
                                countPoison--;
                                countFood++;
                                break;
                            case WALL:
                                pB->indexUp(WALL + 1);
                                break;

                        }
                    }

                    if (24 <= cmd && cmd <= 31) {
                        //turn
                        (count >= 10) ? (runBot = false) : count++;
                        pB->indexUp(cmd);
                        pB->setFocus((pB->getFocus() + cmd - 24) % 8);
                    }

                    if (32 <= cmd && cmd <= 64) {
                        //miss
                        (count >= 10) ? (runBot = false) : count++;
                        pB->indexUp(cmd);
                    }
                }
                pB->upLife(-1);
                if (!pB->isLife()){
                    pB->setStatus(FOOD);
                    countBot--;
                    countFood++;
                }
            }
        }
}

bot world::getElem(int x, int y) {
    return W[x][y];
}

world::world(int bot, int food, int poison, int wall) {
    srand(time(0));
    countBot = 0;
    countFood = 0;
    countPoison = 0;
    countWall = 0;
    for (int i = 0; i < worldX; i++)
        for (int j = 0; j < worldY; j++) {
            W[i][j].setPosX((float)i);
            W[i][j].setPosY((float)j);
            W[i][j].genCDM();
        }

    while (countBot != bot)
        if (!W[rand() % worldX][rand() % worldY].getStatus()) {
            W[rand() % worldX][rand() % worldY].setStatus(BOT);
            countBot++;
        }
    
    while (countFood != food)
        if (!W[rand() % worldX][rand() % worldY].getStatus()) {
            W[rand() % worldX][rand() % worldY].setStatus(FOOD);
            countFood++;
        }
    
    while (countPoison != poison)
        if (!W[rand() % worldX][rand() % worldY].getStatus()) {
            W[rand() % worldX][rand() % worldY].setStatus(POISON);
            countPoison++;
        }
    while (countWall != wall)
        if (!W[rand() % worldX][rand() % worldY].getStatus()) {
            W[rand() % worldX][rand() % worldY].setStatus(WALL);
            countWall++;
        }
}

world::~world() {
}

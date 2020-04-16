#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <time.h>
#include <stdlib.h>

#define MAX_CMD 64

#define EMPTY 0
#define BOT 1
#define FOOD 2
#define POISON 3
#define WALL 4

class element {
private:
    int hp;
    int indexCMD;
    int cmds[MAX_CMD];
    int focus;
    int status;
    bool action;

public:
    void genCDM(int c, int a = 0, int b = MAX_CMD - 1);
    void actionON();
    void actionOFF();
    bool isAction();
    void indexUp();
    void indexUp(int up);
    int getCMD();
    int getCMD(int index);
    void setCMD(int index, int cmd);
    void setFocus(int f);
    int getFocus();
    int getLife();
    void setLife(int i);
    void upLife(int i);
    bool isLife();
    int getStatus();
    void setStatus(int st);
    
    element();
    element(int st);
    ~element();
};

#endif
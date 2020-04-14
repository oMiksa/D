#ifndef BOT_HPP
#define BOT_HPP

#include "elements.hpp"
#include <time.h>
#include <stdlib.h>

#define MAX_CMD 64

class bot : public elements {
private:
    int hp;
    int indexCMD;
    int cmds[MAX_CMD];
    int focus;

public:
    void genCDM();
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
    bot();
    bot(int st, float x, float y);
    ~bot();
};

#endif
#include "bot.hpp"
void bot::indexUp() {
    indexCMD = (indexCMD + 1) % MAX_CMD;
}

void bot::indexUp(int up) {
    indexCMD = (indexCMD + up) % MAX_CMD;
}

int bot::getCMD() {
    return cmds[indexCMD];
}

void bot::genCDM() {
    static int a = 0;
    srand(time(NULL) + a);
    for (int i = 0; i < MAX_CMD; i++)
        cmds[i] = rand() % (MAX_CMD / 2);
}

int bot::getCMD(int index) {
    return cmds[index];
}

void bot::setCMD(int index, int cmd) {
    cmds[index] = cmd;
}

void bot::setFocus(int x) {
    focus = x;
}

int bot::getFocus() {
    return focus;
}
int bot::getLife() {
    return hp;
}

void bot::setLife(int i) {
    hp = i;
}

void bot::upLife(int i) {
    hp += i;
}

bool bot::isLife() {
    return hp > 0;
}

bot::bot() : elements() {
    indexCMD = 0;
    hp = 0;
    focus = 0;
}

bot::bot(int st, float x, float y) : elements(st, x, y) {
    indexCMD = 0;
    hp = 90;
    focus = 0;
}

bot::~bot() {

}

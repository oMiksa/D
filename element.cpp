#include "element.hpp"

void element::indexUp() {
    indexCMD = (indexCMD + 1) % MAX_CMD;
}

void element::indexUp(int up) {
    indexCMD = (indexCMD + up) % MAX_CMD;
}

int element::getCMD() {
    return cmds[indexCMD];
}

void element::genCDM(int c, int a, int b) {
    srand(time(NULL) + c);
    for (int i = 0; i < MAX_CMD; i++) {
        cmds[i] = a + rand() % (b + 1);
    }
}

int element::getCMD(int index) {
    return cmds[index];
}

void element::setCMD(int index, int cmd) {
    cmds[index] = cmd;
}

void element::setFocus(int x) {
    focus = x;
}

int element::getFocus() {
    return focus;
}
int element::getLife() {
    return hp;
}

void element::setLife(int i) {
    hp = i;
}

void element::upLife(int i) {
    hp += i;
}

bool element::isLife() {
    return hp > 0;
}

bool element::isAction() {
    return action;
}

element::element() {
    indexCMD = 0;
    hp = 0;
    focus = 0;
    status = EMPTY;
    action = false;
}

element::element(int st) {
    indexCMD = 0;
    hp = 90;
    focus = 0;
    status = st;
    action = false;
}

element::~element() {

}

void element::actionON() {
    action = true;
}

void element::actionOFF() {
    action = false;
}

int element::getStatus() {
    return status;
}

void element::setStatus(int st) {
    status = st;
}    

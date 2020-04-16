#include "elements1.hpp"

float elements::getPosX() {
    return posX;
}

float elements::getPosY() {
    return posY;
}

void elements::setPosX(float x) {
    posX = x;
}

void elements::setPosY(float y) {
    posY = y;
}

int elements::getStatus() {
    return status;
}

void elements::setStatus(int st) {
    status = st;
}    

elements::elements() {
    status = 0;
    posX = 0.0f;
    posY = 0.0f;
}

elements::elements(int st, float px, float py) {
    status = st;
    posX = px;
    posY = py;
}

elements::~elements() {
}

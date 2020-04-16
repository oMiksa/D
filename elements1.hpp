#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

class elements {
private:
    int status;
    float posX, posY;

public:
    virtual float getPosX();
    virtual float getPosY();
    virtual void setPosX(float x);
    virtual void setPosY(float y);
    virtual int getStatus();
    virtual void setStatus(int st);
    elements();
    elements(int status, float px, float py);
    ~elements();
};

#endif
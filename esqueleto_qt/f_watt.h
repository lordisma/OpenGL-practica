#ifndef F_WATT_H
#define F_WATT_H

#include "obj3drev.h"
#include "objetos.h"
#include "vertex.h"

const float TAMANIO = 7;
const float BRAZO_LEN = 3 * TAMANIO / 4;
const float ANGLE_DEFAULT = 45;
const float WID_PLA = 0.5;
const float LEN_PLA = 1;

const int NUM_STEP = 360;
const float END_CI = 360;


class Bola{
private:
    float angle_ini;
    float angle_ini_rad;
public:
    Bola();
    Bola(float angle);
    void draw(const bool mode []);
};

class Brazo{
private:
    float angle_ini;
    float angle_ini_rad;
public:
    Brazo();
    Brazo(float angle);
    void draw(const bool mode []);
};

class Head{
private:
    float angle_ini;
    float angle_ini_rad;
public:
    Head();
    Head(float angle);
    void draw(const bool mode []);
};

class Body{
private:
    float angle_ini;
    float angle_ini_rad;
public:
    Body();
    Body(float angle);
    void draw(const bool mode []);
};

class Middle{
private:
    float angle_ini;
    float angle_ini_rad;
public:
    Middle();
    Middle(float angle);
    void draw(const bool mode []);
};

class F_Watt
{
private:
    float angle_ini;
    float angle_ini_rad;
public:
    F_Watt();
    F_Watt(float angle);
    void draw();
    void draw(float angle, float paso,const bool mode []);
};

#endif // F_WATT_H

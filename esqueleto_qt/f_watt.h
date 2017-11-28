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
    Esfera esfera;
public:
    Bola();
    void draw(const bool mode []);
};

class Brazo{
private:
    Tubo brazo;
    Bola mano;
    Objeto3D beetho;
public:
    Brazo();
    void draw(const bool mode []);
};

class BrazoDef{
private:
    float angle_ini;
    float angle_ini_rad;

    Brazo brazo;
    Cilindro sug1;
public:
    BrazoDef();
    BrazoDef(float angle);
    void draw(const bool mode []);
};

class Head{
private:
    float angle_ini;
    float angle_ini_rad;

    Brazo der;
    Cilindro cabeza;
public:
    Head();
    Head(float angle);
    void draw(const bool mode []);
};

class Middle{
private:
    float angle_ini;
    float angle_ini_rad;

    Cilindro body;
    Cilindro sug1;
    Cubo     pipote;
public:
    Middle();
    Middle(float angle);
    void draw(const bool mode []);
};

class Body{
private:
    float angle_ini;
    float angle_ini_rad;

    Cilindro cabeza;
    Cilindro cadera;
    Cubo     pipote;
    BrazoDef brazo;
public:
    Body();
    Body(float angle);
    void draw(const bool mode []);
};

class F_Watt
{
private:
    float angle_ini;
    float angle_ini_rad;

    Cilindro base;
    Body cuerpo;
public:
    F_Watt();
    F_Watt(float angle);
    void draw();
    void draw(float angle, float paso,const bool mode []);
};

#endif // F_WATT_H

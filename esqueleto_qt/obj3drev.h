#ifndef OBJ3DREV_H
#define OBJ3DREV_H

#include <vector>
#include <math.h>
#include "vertex.h"
#include "objetos.h"
#include <iostream>

const unsigned int DEFAULT_CUT = 10;
const float PI = 2* acos(0.0);

class Obj3DRev:public Objeto3D
{
public:
    Obj3DRev();
    Obj3DRev(const string &file_ply);

    unsigned int GetNumCut ();
    void SetNumCut (unsigned int newcut);

    void CreateGeometryY(); //Rotacion entorno al eje Y
    void CreateGeometryY(float angle_ini,float angle_end);

private:
    unsigned int num_cut;
};

class Cilindro:public Obj3DRev
{
  public:
    Cilindro();
    Cilindro(float angle_ini,float angle_end,unsigned int num_cut);
};

class Cono:public Obj3DRev
{
  public:
    Cono();
};

class Vaso:public Obj3DRev
{
public:
    Vaso();
};

class VasoI:public Obj3DRev
{
public:
    VasoI();
};

class Tubo:public Obj3DRev
{
   public:
    Tubo();
};
class Peon:public Obj3DRev
{
   public:
    Peon();
};

class Esfera:public Obj3DRev
{
  public:
    Esfera();
};

#endif // OBJ3DREV_H

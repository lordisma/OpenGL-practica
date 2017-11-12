#ifndef OBJETOS_H
#define OBJETOS_H
/**
  * @Author: Ismael Marín Molina
  * @date: 27-09-2017
  * @def: Clases para la implementacion de figuras geométricas
  *     y su dibujo haciendo uso de OPENGL en Qt.
  *
  */
#include <vector>
#include "vertex.h"
#include "_file_ply.h"
#include <utility>


const float RADIO = 1;

class Objeto3DPuntos {
public:

    Objeto3DPuntos (const vector<_vertex3f > & Puntos);
    Objeto3DPuntos (float x_axis, float y_axis, float z_axis );
    Objeto3DPuntos () {}
    Objeto3DPuntos(float vertex []);//Genera un punto con las coordenadas
    Objeto3DPuntos (const Objeto3DPuntos &p);

    void draw_points();

    void insert_point (float x_axis, float y_axis, float z_axis);
    void insert_point (float vertex []);

    void operator =(const Objeto3DPuntos &p);


protected:
    vector<_vertex3f > Vertices;

private:


};

class Objeto3D : public Objeto3DPuntos {

public:
    typedef _vertex3i Triangulo;

    Objeto3D(){}
    Objeto3D(float x_axis, float y_axis, float z_axis);
    Objeto3D(float vertex []);
    Objeto3D(const Objeto3D &p);
    Objeto3D(const string &file_ply);

    void MakeFace (vector <Triangulo> caras);
    void MakeFace (int caras []);

    void draw_line();
    void draw_fill();
    void draw_chess();

    void TransformPLY(const string &file_ply);

    void insert_line (float v_ini [], float v_end []);

    void operator =(const Objeto3D &p);

protected:
    vector < Triangulo> Triangulos;

private:


};

/////////////////////////////////////////////////////////////

/**
  * @Author: Ismael Marín Molina
  * @date: 27-09-2017
  * @def:Figuras geométricas variadas
  */

//////////////////////////////////////////////////////////////

class Cubo : public Objeto3D{
  public:
    Cubo();
    Cubo(const Cubo &p);
    Cubo(float x, float y, float z, float size);

    void draw();
    void drawl();
    void drawp();
    void drawc();

};

class Tetraedro: public Objeto3D{
  public:
    Tetraedro();
    Tetraedro(const Tetraedro &p);
    Tetraedro(float x, float y, float z, float size);

    void draw();
    void drawl();
    void drawp();
    void drawc();

};

class Piramide: public Objeto3D{
    public:
        Piramide();
        Piramide(const Piramide &p);
        Piramide(float x, float y, float z, float size);

        void draw();
        void drawl();
        void drawp();
        void drawc();
};



#endif // OBJETOS_H

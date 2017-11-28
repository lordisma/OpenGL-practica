#include "objetos.h"
#include <GL/glew.h>
#include <QOpenGLWidget>


Objeto3DPuntos::Objeto3DPuntos (const vector<_vertex3f > &Puntos){
    Vertices = Puntos;
}

Objeto3DPuntos::Objeto3DPuntos(float vertex []){
    this->insert_point(vertex);
}

Objeto3DPuntos::Objeto3DPuntos (float x_axis, float y_axis, float z_axis) {
    this->insert_point(x_axis, y_axis, z_axis);
}

Objeto3DPuntos::Objeto3DPuntos(const Objeto3DPuntos &p){
    Vertices = p.Vertices;
}

void Objeto3DPuntos::draw_points(){
    unsigned int i = 0;
    glColor3f(0,1,0);
    glPointSize(4);

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    glBegin(GL_POINTS);
    for (i=0;i<Vertices.size();i++){
      glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
      }
    glEnd();
}

void Objeto3DPuntos::insert_point(float x_axis, float y_axis, float z_axis){
    _vertex3f temp (x_axis, y_axis, z_axis);

    Vertices.push_back(temp);
}

void Objeto3DPuntos::insert_point(float vertex []){
    _vertex3f temp (vertex[0], vertex[1], vertex[2]);

    Vertices.push_back(temp);
}

void Objeto3DPuntos::operator =(const Objeto3DPuntos &p){
    Vertices = p.Vertices;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Objeto3D::Objeto3D (float x_axis, float y_axis, float z_axis){
    this->insert_point(x_axis,y_axis,z_axis);
}

Objeto3D::Objeto3D (float vertex []){
    this->insert_point(vertex);
}

Objeto3D::Objeto3D (const Objeto3D &p){

    Vertices = p.Vertices;
    Triangulos = p.Triangulos;

}

Objeto3D::Objeto3D(const string &file_ply){

    _file_ply reader;

   if (reader.open(file_ply))
       reader.read(Vertices, Triangulos);

}

void Objeto3D::MakeFace(vector<Triangulo> caras){
    Triangulos = caras;
}

void Objeto3D::MakeFace(int caras []){
    Triangulo tem (caras[0], caras [1], caras[2]);

    Triangulos.push_back(tem);
}

void Objeto3D::insert_line(float v_ini[], float v_end[]){
    this->insert_point(v_ini);
    this->insert_point(v_end);
}

void Objeto3D::draw_line(){
    glColor3f(1,0,0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);

    for (unsigned int i = 0; i < Triangulos.size(); i++){

        glVertex3f(Vertices[Triangulos[i].x].x, Vertices[Triangulos[i].x].y, Vertices[Triangulos[i].x].z);//Vertice 1 del triangulo
        glVertex3f(Vertices[Triangulos[i].y].x, Vertices[Triangulos[i].y].y, Vertices[Triangulos[i].y].z);//Vertice 2 del triangulo
        glVertex3f(Vertices[Triangulos[i].z].x, Vertices[Triangulos[i].z].y, Vertices[Triangulos[i].z].z);//Vertice 3 del triangulo

    }
    glEnd();
}

void Objeto3D::draw_fill(){
    glColor3f(0,1,1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);

        for (unsigned int i = 0; i < Triangulos.size(); i++){
                glVertex3f(Vertices[Triangulos[i].x].x, Vertices[Triangulos[i].x].y, Vertices[Triangulos[i].x].z);//Vertice 1 del triangulo
                glVertex3f(Vertices[Triangulos[i].y].x, Vertices[Triangulos[i].y].y, Vertices[Triangulos[i].y].z);//Vertice 2 del triangulo
                glVertex3f(Vertices[Triangulos[i].z].x, Vertices[Triangulos[i].z].y, Vertices[Triangulos[i].z].z);//Vertice 3 del triangulo
        }

    glEnd();
}

void Objeto3D::draw_chess(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);

        for (unsigned int i = 0; i < Triangulos.size(); i++){
            glColor3f(0,0,i%2);//Ajedrez
                glVertex3f(Vertices[Triangulos[i].x].x, Vertices[Triangulos[i].x].y, Vertices[Triangulos[i].x].z);//Vertice 1 del triangulo
                glVertex3f(Vertices[Triangulos[i].y].x, Vertices[Triangulos[i].y].y, Vertices[Triangulos[i].y].z);//Vertice 2 del triangulo
                glVertex3f(Vertices[Triangulos[i].z].x, Vertices[Triangulos[i].z].y, Vertices[Triangulos[i].z].z);//Vertice 3 del triangulo

        }

    glEnd();
}

void Objeto3D::operator =(const Objeto3D &p){
    Vertices = p.Vertices;
    Triangulos = p.Triangulos;
}

void Objeto3D::TransformPLY(const string &file_ply){
    Vertices.clear();
    Triangulos.clear();

    _file_ply reader;

   if (reader.open(file_ply))
       reader.read(Vertices, Triangulos);
}





////////////////////////////////////////////////////CUBO///////////////////////////////////////////////////////////





Cubo::Cubo(const Cubo &p){
    Vertices = p.Vertices;
    Triangulos = p.Triangulos;
}

Cubo::Cubo(){
    float r = RADIO;

    Vertices = {{r/2,r/2,r/2},   {r/2,r/2,-r/2},
               {r/2,-r/2,r/2},  {r/2,-r/2,-r/2},
               {-r/2,r/2,r/2},  {-r/2,r/2,-r/2},
               {-r/2,-r/2,r/2}, {-r/2,-r/2,-r/2}};
    Triangulos = {{0,2,3},{3,1,0},{5,7,6},{6,4,5},{1,5,4},{4,0,1},{6,2,3},{3,7,6},{4,6,2},{2,0,4},{1,3,7},{7,5,1}};
}

Cubo::Cubo(float x, float y, float z, float size){
    float r = size;
    Vertices =             {{x + (r/2),y + (r/2),z + (r/2)},   {x + (r/2),y + (r/2),z + (-r/2)},
                           {x + (r/2),y + (-r/2),z + (r/2)},  {x + (r/2),y + (-r/2),z + (-r/2)},
                           {x + (-r/2),y + (r/2),z + (r/2)},  {x + (-r/2),y + (r/2),z + (-r/2)},
                           {x + (-r/2),y + (-r/2),z + (r/2)}, {x + (-r/2),y + (-r/2),z + (-r/2)}};
    Triangulos = {{0,1,2},{3,2,1},{4,5,0},{1,0,5},{0,2,4},{6,4,2},{5,7,1},{3,1,7},{7,6,3},{2,3,6},{4,6,5},{7,5,6}}; //Importante el orden para el dibujo de las lineas
}

void Cubo::draw(){

    draw_fill();

}

void Cubo::drawl(){

    draw_line();

}

void Cubo::drawp(){

    draw_points();

}

void Cubo::drawc(){

    draw_chess();

}




/////////////////////////////////////////////////////////////Tetraedro////////////////////////////////////////////////////////////////////



Tetraedro::Tetraedro(const Tetraedro &p){
    Vertices = p.Vertices;
    Triangulos = p.Triangulos;
}

Tetraedro::Tetraedro(){
    float r = RADIO;
    Vertices = {{0,r/2,0},{r/2,-r/2,-r/2},{0,-r/2,r/2},{-r/2,-r/2,-r/2}};
    Triangulos = {{0,1,2},{3,0,2},{1,3,2},{1,0,3}};
}

Tetraedro::Tetraedro(float x, float y, float z, float size){
    float r = size;
    Vertices = {{x,y +(r/2),z},{x +(r/2),y +(-r/2),z +(-r/2)},
                             {x,y +(-r/2),z +(r/2)},{x +(-r/2),y +(-r/2),z +(-r/2)}};
    Triangulos = {{0,1,2},{3,0,2},{1,3,2},{1,0,3}};

}

void Tetraedro::draw(){
    draw_fill();
}

void Tetraedro::drawl(){
    draw_line();
}

void Tetraedro::drawp(){
    draw_points();
}

void Tetraedro::drawc(){
    draw_chess();
}

/////////////////////////////////////////////////////////////PIRAMIDE/////////////////////////////////////////////////////////////

Piramide::Piramide(){
    float r = RADIO;
    Vertices = {{0,r/2,0},{r/2,-r/2,r/2},{r/2,-r/2,-r/2},{-r/2,-r/2,-r/2},{-r/2,-r/2,r/2}};
    Triangulos = {{0,2,3},{0,1,2},{0,1,4},{0,4,3},{4,3,1},{2,1,3}};

}

Piramide::Piramide(const Piramide &p){
    Vertices = p.Vertices;
    Triangulos = p.Triangulos;
}

Piramide::Piramide(float x, float y, float z, float size){
    float r = size;
    Vertices = {{x,y + (r/2),z},
                             {x + (r/2),y + (-r/2),z + (r/2)},
                             {x + (r/2),y + (-r/2),z + (-r/2)},
                             {x + (-r/2),y + (-r/2),z + (-r/2)},
                             {x + (-r/2),y + (-r/2),z + (r/2)}};
    Triangulos = {{0,2,3},{0,1,2},{0,1,4},{0,4,3},{4,3,1},{2,1,3}};
}

void Piramide::draw(){
    draw_fill();
}

void Piramide::drawl(){
    draw_line();
}

void Piramide::drawp(){
    draw_points();
}

void Piramide::drawc(){
    draw_chess();
}


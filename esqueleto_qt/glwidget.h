#ifndef GLWIDGET_H
#define GLWIDGET_H
//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <iostream>
#include "vertex.h"
#include "objetos.h"
#include "obj3drev.h"
#include "f_watt.h"

namespace _gl_widget_ne {

  const _vertex3f COLORS[]={{0,0,0},{1,0,0},{0,1,0},{0,0,1},{0,1,1},{1,0,1},{1,1,0},{1,1,1}};

  const float X_MIN=-1;
  const float X_MAX=1;
  const float Y_MIN=-1;
  const float Y_MAX=1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=10;

  const float ANGLE_STEP=1;

  // axis
  const int AXIS_SIZE=5000;
  const unsigned int CUBO = 1, TETRA = 0, PIRA = 5, PLY = 3, REV = 2, FIG = 6;
  const float angleInitial = 40;
}


class _window;

class _gl_widget : public QOpenGLWidget
{
    Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();

  void load_ply(const string & ply_file);

public slots:
  void pinta ();

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;
  inline bool isAnima() const {return isAnimated;}


private:
  _window *Window;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;

  float angle;

  unsigned int Key;
  bool mode [4];//{0:point,1:line,2:fill,3:chess}
  bool figure[6];//{Q:cilinder,W:cube,E:Vaso,R:Tube,T:Peon,Y:Vaso Inverso}

  float pasos;//variable para indicar el paso de giro
  bool isAnimated;

  Tetraedro tetra;
  Cubo cubo;
  Piramide pira;
  Peon peo;
  Cilindro cili;
  Cono con;
  Vaso vas;
  VasoI vasi;
  Tubo tub;
  Objeto3D ply;
  F_Watt fig;
  QTimer * timer = new QTimer(this);

};

#endif

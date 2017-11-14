//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include "glwidget.h"
#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <math.h>
#include "objetos.h"
#include "obj3drev.h"

#include "window.h"

using namespace std;
using namespace _gl_widget_ne;

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  if(connect(timer, SIGNAL(timeout()), SLOT(pinta())) ) cout << "\nConnection recibida\n";
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}

//*************************************************************************
//Funcion de pintado de la animacion
//*************************************************************************

void _gl_widget::pinta(){

    if(isAnima()) pasos = pasos + 4 * PI * angle / NUM_STEP;

    if(pasos >= NUM_STEP) pasos = pasos - NUM_STEP;

    fig.draw(angle, pasos, mode);

    //timer->start(60000);
    update();
}

//*************************************************************************
//Handler de entrada por teclado
//*************************************************************************
void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){

  //Aqui tenemos el recolector de eventos
  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:Observer_distance*=1.2;break;
  case Qt::Key_PageDown:Observer_distance/=1.2;break;


  // Control funciones basicas
  case Qt::Key_1: Key=1;break;
  case Qt::Key_0: Key=0;break;
  case Qt::Key_5: Key=5;break;
  case Qt::Key_3: Key=3;break;
  case Qt::Key_2: Key=2;break;

  // Control modo de dibujo
  case Qt::Key_L: (mode[1])? mode[1] = false:mode[1] = true;break;
  case Qt::Key_P: (mode[0])? mode[0] = false:mode[0] = true;break;
  case Qt::Key_F: (mode[2])? mode[2] = false:mode[2] = true;    mode[3]=false;  break;
  case Qt::Key_C: (mode[3])? mode[3] = false:mode[3] = true;    mode[2]=false;  break;

  // Objetos por revolucion
  case Qt::Key_Q: (figure[0] && Key == 2)? figure[0]=false:figure[0]=true;break;
  case Qt::Key_W: (figure[1] && Key == 2)? figure[1]=false:figure[1]=true;break;
  case Qt::Key_E: (figure[2] && Key == 2)? figure[2]=false:figure[2]=true;break;
  case Qt::Key_R: (figure[3] && Key == 2)? figure[3]=false:figure[3]=true;break;
  case Qt::Key_T: (figure[4] && Key == 2)? figure[4]=false:figure[4]=true;break;
  case Qt::Key_Y: (figure[5] && Key == 2)? figure[5]=false:figure[5]=true;break;

  // Control de figura animada
  case Qt::Key_6: Key = 6;break;

  case Qt::Key_K: (angle < 84)? angle+=1:angle=84;break;
  case Qt::Key_J: (angle > 20)? angle-=1:angle=20;break;

  case Qt::Key_S:     if(isAnima()){
                        isAnimated = false;
                        timer->stop();
                      }else{
                        isAnimated = true;
                        timer->start(60000);
                      }
                      break;


  }

  update();//Pinta cuando puedas
}

//**************************************************************************
//
//***************************************************************************

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  //  Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void _gl_widget::draw_axis()
{
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1,0,0);
  glVertex3f(-AXIS_SIZE,0,0);
  glVertex3f(AXIS_SIZE,0,0);
  // eje Y, color verde
  glColor3f(0,1,0);
  glVertex3f(0,-AXIS_SIZE,0);
  glVertex3f(0,AXIS_SIZE,0);
  // eje Z, color azul
  glColor3f(0,0,1);
  glVertex3f(0,0,-AXIS_SIZE);
  glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void _gl_widget::draw_objects()
{

    switch (Key) {
    case CUBO:
        if (mode[1]) cubo.drawl();
        if (mode[0]) cubo.drawp();
        if (mode[3]) cubo.drawc();
        if (mode[2]) cubo.draw();
        break;
     case TETRA:
        if (mode[1]) tetra.drawl();
        if (mode[0]) tetra.drawp();
        if (mode[3]) tetra.drawc();
        if (mode[2]) tetra.draw();
        break;
     case PIRA:
       if (mode[1]) pira.drawl();
       if (mode[0]) pira.drawp();
       if (mode[3]) pira.drawc();
       if (mode[2]) pira.draw();
       break;
     case PLY:
        if (mode[1]) ply.draw_line();
        if (mode[0]) ply.draw_points();
        if (mode[3]) ply.draw_chess();
        if (mode[2]) ply.draw_fill();
       break;        
    case REV:

       if(figure[0]){
        if (mode[1]) cili.draw_line();
        if (mode[0]) cili.draw_points();
        if (mode[3]) cili.draw_chess();
        if (mode[2]) cili.draw_fill();
       }else

       if(figure[1]){
        if (mode[1]) con.draw_line();
        if (mode[0]) con.draw_points();
        if (mode[3]) con.draw_chess();
        if (mode[2]) con.draw_fill();
       }else

       if(figure[2]){
        if (mode[1]) vas.draw_line();
        if (mode[0]) vas.draw_points();
        if (mode[3]) vas.draw_chess();
        if (mode[2]) vas.draw_fill();
       }else

       if(figure[3]){
        if (mode[1]) tub.draw_line();
        if (mode[0]) tub.draw_points();
        if (mode[3]) tub.draw_chess();
        if (mode[2]) tub.draw_fill();
       }else

       if(figure[4]){
        if (mode[1]) peo.draw_line();
        if (mode[0]) peo.draw_points();
        if (mode[3]) peo.draw_chess();
        if (mode[2]) peo.draw_fill();
       }else

       if(figure[5]){
        if (mode[1]) vasi.draw_line();
        if (mode[0]) vasi.draw_points();
        if (mode[3]) vasi.draw_chess();
        if (mode[2]) vasi.draw_fill();
       }
      break;
    case FIG:
        pinta();
        break;
    default:
        break;
    }

}


//*************************************************************************
//
//*************************************************************************

void _gl_widget::paintGL()
{
  //Cada vez que pinta, pinta todo
  clear_window();
  change_projection();
  change_observer();
  draw_axis();
  draw_objects();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
}


//*************************************************************************
//Inicializador de la clase
//*************************************************************************

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
    }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit (-1);
    }

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;
  Key = 0;

  for(int i = 0; i < 4; i++)
      mode[i] = false;

  for(int i = 0; i < 7; i++)
      figure[i] = false;


  // Para que al iniciar aparezca algo
  mode[0] = true; Key = 1; figure[3] = true;


  angle = angleInitial;
  isAnimated = false;

  pasos = 0;
}

/*******************
 *
 *
 *******************/
void _gl_widget::load_ply(const string & ply_file){
        ply = Objeto3D(ply_file);

        update();
}


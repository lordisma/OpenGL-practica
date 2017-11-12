#include "f_watt.h"
#include <GL/glew.h>
#include <QOpenGLWidget>

Bola::Bola(){    
    angle_ini = ANGLE_DEFAULT;
    angle_ini_rad = angle_ini * PI/180;
}

Bola::Bola(float angle){
    angle_ini = angle;
    angle_ini_rad = angle_ini * PI/180;
}

void Bola::draw(const bool mode []){
 Esfera esfera;

 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
 glTranslatef(-(std::sin(angle_ini_rad) * BRAZO_LEN/2),-(std::cos(angle_ini_rad) * BRAZO_LEN/2),0);
 glRotatef(-angle_ini,0,0,1);

 if (mode[1]) esfera.draw_line();
 if (mode[0]) esfera.draw_points();
 if (mode[3]) esfera.draw_chess();
 if (mode[2]) esfera.draw_fill();

 glPopMatrix();
}

Brazo::Brazo(){
 angle_ini = ANGLE_DEFAULT;
 angle_ini_rad = angle_ini * PI/180;
}

Brazo::Brazo(float angle){
    angle_ini = angle;
    angle_ini_rad = angle_ini * PI/180;
}

void Brazo::draw(const bool mode []){
    Tubo brazo;
    Bola mano{angle_ini};

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glRotatef(-angle_ini,0,0,1);
    glScalef(LEN_PLA/4,BRAZO_LEN,LEN_PLA/4);
    if (mode[1]) brazo.draw_line();
    if (mode[0]) brazo.draw_points();
    if (mode[3]) brazo.draw_chess();
    if (mode[2]) brazo.draw_fill();
    glPopMatrix();


    glPushMatrix();
    mano.draw(mode);
    glPopMatrix();
}

Head::Head(){
    angle_ini = ANGLE_DEFAULT;
    angle_ini_rad = angle_ini * PI/180;
}

Head::Head(float angle){
    angle_ini = angle;
    angle_ini_rad = angle_ini * PI/180;
}

void Head::draw(const bool mode []){
    Brazo der{angle_ini},izq{angle_ini};
    Cilindro cabeza;

    glMatrixMode(GL_MODELVIEW);

    //Brazo derecho
    glPushMatrix();
    glTranslatef(-(std::sin(angle_ini_rad) * (BRAZO_LEN/2)) - WID_PLA + (LEN_PLA/8 * std::cos(angle_ini_rad)) ,
                                                                      std::cos(angle_ini_rad) * (BRAZO_LEN/2) ,
                                                                                                           0 );
    der.draw(mode);
    glPopMatrix();

    //Brazo izquierdo
    glPushMatrix();
    glTranslatef((std::sin(angle_ini_rad) * (BRAZO_LEN/2) + WID_PLA) - (LEN_PLA/8 * std::cos(angle_ini_rad)),std::cos(angle_ini_rad) * (BRAZO_LEN/2),0);
    glRotatef(180,0,1,0);
    izq.draw(mode);
    glPopMatrix();

    //Cabeza
    glPushMatrix();
    glTranslatef(0, std::cos(angle_ini_rad) * (BRAZO_LEN)  ,0);
    glScalef(LEN_PLA,WID_PLA,LEN_PLA);
    if (mode[1]) cabeza.draw_line();
    if (mode[0]) cabeza.draw_points();
    if (mode[3]) cabeza.draw_chess();
    if (mode[2]) cabeza.draw_fill();
    glPopMatrix();


}

Body::Body(){
    angle_ini = ANGLE_DEFAULT;
    angle_ini_rad = angle_ini * PI/180;
}

Body::Body(float angle){
    angle_ini = angle;
    angle_ini_rad = angle_ini * PI/180;
}

void Body::draw(const bool mode []){
    Head cabeza{angle_ini};
    Middle cadera{angle_ini};

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(0,WID_PLA/2,0);
    cabeza.draw(mode);
    glPopMatrix();

    glPushMatrix();
    cadera.draw(mode);
    glPopMatrix();

}

Middle::Middle(){
    angle_ini = ANGLE_DEFAULT;
    angle_ini_rad = angle_ini * PI/180;
}

Middle::Middle(float angle){
    angle_ini = angle;
    angle_ini_rad = angle_ini * PI/180;
}

void Middle::draw(const bool mode []){
    Cilindro body;
    Cilindro sug1,sug2;
    Cubo     pipote;

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(0,WID_PLA/2,0);
    glScalef(LEN_PLA,WID_PLA,LEN_PLA);
    if (mode[1]) body.draw_line();
    if (mode[0]) body.draw_points();
    if (mode[3]) body.draw_chess();
    if (mode[2]) body.draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3*LEN_PLA/8,-(3*BRAZO_LEN/4 - (std::cos(20) * BRAZO_LEN))/2,0);
    glScalef(LEN_PLA/8,3*BRAZO_LEN/4 - (std::cos(20) * BRAZO_LEN), LEN_PLA/8);
    if (mode[1]) pipote.drawl();
    if (mode[0]) pipote.drawp();
    if (mode[3]) pipote.drawc();
    if (mode[2]) pipote.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef((std::sin(angle_ini_rad) * BRAZO_LEN/4) + WID_PLA - (std::cos(angle_ini_rad) * LEN_PLA/8),(std::cos(angle_ini_rad) * BRAZO_LEN/4) + WID_PLA/2 , 0);
    glRotatef(-angle_ini,0,0,1);
    glScalef(LEN_PLA/4,BRAZO_LEN/2,LEN_PLA/4);
    if (mode[1]) sug1.draw_line();
    if (mode[0]) sug1.draw_points();
    if (mode[3]) sug1.draw_chess();
    if (mode[2]) sug1.draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(std::sin(angle_ini_rad) * BRAZO_LEN/4) - WID_PLA + (std::cos(angle_ini_rad) * LEN_PLA/8),(std::cos(angle_ini_rad) * BRAZO_LEN/4) + WID_PLA/2 , 0);
    glRotatef(angle_ini,0,0,1);
    glScalef(LEN_PLA/4,(BRAZO_LEN/2),LEN_PLA/4);
    if (mode[1]) sug2.draw_line();
    if (mode[0]) sug2.draw_points();
    if (mode[3]) sug2.draw_chess();
    if (mode[2]) sug2.draw_fill();
    glPopMatrix();

}



F_Watt::F_Watt()
{
    angle_ini = ANGLE_DEFAULT;
    angle_ini_rad = angle_ini * PI/180;
}

F_Watt::F_Watt(float angle){
    angle_ini = angle;
    angle_ini_rad = angle_ini * PI/180;
}

void F_Watt::draw(float angle, float paso, const bool mode []){
    angle_ini = angle;
    angle_ini_rad = angle_ini * PI/180;

    Cilindro base,columna;
    Body cuerpo{angle_ini};

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(0,0.1,0);
    glScalef(5,0.2,5);
    if (mode[1]) base.draw_line();
    if (mode[0]) base.draw_points();
    if (mode[3]) base.draw_chess();
    if (mode[2]) base.draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, ( (TAMANIO /*+ (std::cos(angle_ini_rad) * (BRAZO_LEN))*/) /2) + 0.2, 0);
    glScalef(LEN_PLA/4,TAMANIO /*+ (std::cos(angle_ini_rad) * (BRAZO_LEN))*/,LEN_PLA/4);
    if (mode[1]) columna.draw_line();
    if (mode[0]) columna.draw_points();
    if (mode[3]) columna.draw_chess();
    if (mode[2]) columna.draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,TAMANIO - (std::cos(angle_ini_rad) * (BRAZO_LEN)),0);
    glRotatef(paso * END_CI / NUM_STEP,0,1,0);
    cuerpo.draw(mode);
    glPopMatrix();
}


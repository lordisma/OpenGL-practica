#include "obj3drev.h"

Obj3DRev::Obj3DRev() : num_cut(DEFAULT_CUT){}
Obj3DRev::Obj3DRev(const string &file_ply) : num_cut(DEFAULT_CUT), Objeto3D(file_ply){}

unsigned int Obj3DRev::GetNumCut(){
    return num_cut;
}

void Obj3DRev::SetNumCut(unsigned int newcut){
    this ->num_cut = newcut;
}

void Obj3DRev::CreateGeometryY(){

    int tamanio_vector = Vertices.size(), nuevo_tamanio, i, j, inicio=0,limite;
    float angle, coseno, seno;
    pair <bool,int> tapsup (false,0);
    pair <bool,int> tapinf (false,0);

    Vertices.reserve(tamanio_vector * num_cut);

    for (i=0; i < tamanio_vector; i++){

        if (Vertices[i].x == 0.0 && !tapsup.first){
           tapsup = pair<bool,int>{true,i};
        }else if (Vertices[i].x == 0){
           tapinf = pair<bool,int>{true,i};
        }
    }

    if (tapsup.first && tapinf.first){
        if(Vertices[tapsup.second].y < Vertices[tapinf.second].y){
            int aux = tapinf.second;
            tapinf.second = tapsup.second;
            tapsup.second = aux;
        }

    }

    for(i = 1; i < num_cut; i++){
        angle = i * 2 * PI / num_cut;
        coseno = cos(angle); seno = sin(angle);
        for (j = 0; j < tamanio_vector; j++)

          // if ((tapsup.first && tapsup.second == i)  ||  (tapinf.first && tapinf.second == i)) //Obviamos los puntos de las tapas

                Vertices.push_back(
                          _vertex3f(  ( Vertices[j].x * coseno) + (Vertices[j].z * seno),
                                        Vertices[j].y                          ,
                                      -( Vertices[j].x * seno)   + (Vertices[j].z * coseno)
                                    )
                                  );

    }

    Triangulos.clear();//Limpiamos y reservamos la memoria que vamos a usar para el nuevo tamaño
    Triangulos.reserve( tamanio_vector * num_cut );
    nuevo_tamanio = Vertices.size();
    limite = tamanio_vector - 1;

    if(tapinf.first) limite--;
    if(tapsup.first) inicio = 1;


    for(i = inicio; i < limite; i++){
        for(j = 0; j < num_cut; j++ ){

            Triangulos.push_back({
                                    (( i+1    +     (   j   * tamanio_vector))  %  nuevo_tamanio),
                                    (( i      +     (   j   * tamanio_vector))  %  nuevo_tamanio),
                                    (( i      +     ( (j+1) * tamanio_vector))  %  nuevo_tamanio)
                                 });

            Triangulos.push_back({
                                     (( i        +     ( (j+1) * tamanio_vector))  %  nuevo_tamanio),
                                     (( i+1      +     ( (j+1) * tamanio_vector))  %  nuevo_tamanio),
                                     (( i+1      +     (  j    * tamanio_vector))  %  nuevo_tamanio)
                                 });
        }
    }

    if(tapsup.first){

        for(i=tamanio_vector - 2 ; i < nuevo_tamanio ;i += tamanio_vector){
            Triangulos.push_back({
                                     tapsup.second,
                                     i,
                                     ((i + tamanio_vector)  %  nuevo_tamanio)
                                 });
        }

    }

    if(tapinf.first){

        for(i=1 ; i < nuevo_tamanio ;i += tamanio_vector){
            Triangulos.push_back({
                                     tapinf.second,
                                     i,
                                     ((i + tamanio_vector)  %  nuevo_tamanio)
                                 });
        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Obj3DRev::CreateGeometryY(float angle_ini,float angle_end){

    int tamanio_vector = Vertices.size(), nuevo_tamanio, i, j, inicio=0,limite;
    float angle, coseno = cos(angle_ini), seno = sin(angle_ini);
    pair <bool,int> tapsup (false,0);
    pair <bool,int> tapinf (false,0);

    angle = angle_ini;

    Vertices.reserve(tamanio_vector * num_cut);

    for (i=0; i < tamanio_vector; i++){

        if (Vertices[i].x == 0.0 && !tapsup.first){
           tapsup = pair<bool,int>{true,i};
        }else if (Vertices[i].x == 0){
           tapinf = pair<bool,int>{true,i};
        }

        cout<< Vertices[i].x<< " " << Vertices[i].y<< " " <<Vertices[i].z << endl;

        Vertices[i] = _vertex3f{
                            (Vertices[i].x * coseno),
                            Vertices[i].y,
                            (Vertices[i].x * seno)
                        };

         cout<< Vertices[i].x<< " " << Vertices[i].y<< " " <<Vertices[i].z << endl;
    }

    if (tapsup.first && tapinf.first){
        if(Vertices[tapsup.second].y < Vertices[tapinf.second].y){
            int aux = tapinf.second;
            tapinf.second = tapsup.second;
            tapsup.second = aux;
        }

    }

    for(i = 1; i < num_cut; i++){
        angle = i * (angle_end - angle_ini) / num_cut;
        angle = angle + angle_ini;
        coseno = cos(angle); seno = sin(angle);
        for (j = 0; j < tamanio_vector; j++)

          // if ((tapsup.first && tapsup.second == i)  ||  (tapinf.first && tapinf.second == i)) //Obviamos los puntos de las tapas

                Vertices.push_back(
                          _vertex3f(  ( Vertices[j].x * coseno) ,
                                        Vertices[j].y                          ,
                                      ( Vertices[j].x * seno)
                                    )
                                  );

       // angle =  (i*((angle_end - angle_ini) / num_cut)) + angle_ini;

    }

    Triangulos.clear();//Limpiamos y reservamos la memoria que vamos a usar para el nuevo tamaño
    Triangulos.reserve( tamanio_vector * num_cut );
    nuevo_tamanio = Vertices.size();
    limite = tamanio_vector - 1;

    if(tapinf.first) limite--;
    if(tapsup.first) inicio = 1;


    for(i = inicio; i < limite; i++){
        for(j = 0; j < num_cut; j++ ){

            Triangulos.push_back({
                                    (( i+1    +     (   j   * tamanio_vector))  %  nuevo_tamanio),
                                    (( i      +     (   j   * tamanio_vector))  %  nuevo_tamanio),
                                    (( i      +     ( (j+1) * tamanio_vector))  %  nuevo_tamanio)
                                 });

            Triangulos.push_back({
                                     (( i        +     ( (j+1) * tamanio_vector))  %  nuevo_tamanio),
                                     (( i+1      +     ( (j+1) * tamanio_vector))  %  nuevo_tamanio),
                                     (( i+1      +     (  j    * tamanio_vector))  %  nuevo_tamanio)
                                 });
        }
    }

    if(tapsup.first){

        for(i=tamanio_vector - 2 ; i < nuevo_tamanio ;i += tamanio_vector){
            Triangulos.push_back({
                                     tapsup.second,
                                     i,
                                     ((i + tamanio_vector)  %  nuevo_tamanio)
                                 });
        }

    }

    if(tapinf.first){

        for(i=1 ; i < nuevo_tamanio ;i += tamanio_vector){
            Triangulos.push_back({
                                     tapinf.second,
                                     i,
                                     ((i + tamanio_vector)  %  nuevo_tamanio)
                                 });
        }

    }

}



/// ////////////////////////////////////////////////////////////////////////////////////////////////////////

Cilindro::Cilindro(){
    float r = RADIO;

    Vertices = { {0.0,-r/2,0.0},{r/2,-r/2,0.0},
                 {r/2,r/2,0.0},{0.0,r/2,0.0}
                };

    CreateGeometryY();
}

Cilindro::Cilindro(float angle_ini,float angle_end, unsigned int num_cut){
    float r = RADIO;

    Vertices = { {0.0,-r/2,0.0},{r/2,-r/2,0.0},
                 {r/2,r/2,0.0},{0.0,r/2,0.0}
                };

    SetNumCut(num_cut);
    CreateGeometryY(angle_ini,angle_end);
}


Cono::Cono(){
    float r = RADIO;

    Vertices = { {0.0,-r/2,0.0},{r/2,-r/2,0.0},{0.0,r/2,0.0}  };

    CreateGeometryY();
}

Vaso::Vaso(){
    float r = RADIO;

    Vertices = { {0.0,-r/2,0.0},{r/4,-r/2,0.0},{r/2,r/2,0.0}  };

    CreateGeometryY();
}

VasoI::VasoI(){
    float r = RADIO;

    Vertices = { {0.0,r/2,0.0},{r/4,r/2,0.0},{r/2,-r/2,0.0}  };

    CreateGeometryY();
}

Tubo::Tubo(){
    float r = RADIO;

    Vertices = { {r/2,r/2,0.0},{r/2,-r/2,0.0} };

    CreateGeometryY();
}
Peon::Peon(){
    Vertices = {
        {0.0,-1.4,0.0},//Tapa inferior

        {1.0,-1.4,0.0},{1.0,-1.1,0.0},
        {0.5,-0.7,0.0},{0.5,-0.7,0.0},
        {0.5,-0.7,0.0},{0.4,-0.4,0.0},
        {0.4,0.5,0.0},{0.5,0.6,0.0},
        {0.3,0.6,0.0},{0.5,0.8,0.0},
        {0.55,1.0,0.0},{0.5,1.2,0.0},
        {0.3,1.4,0.0},

        {0.0,1.4,0.0}//Tapa Superior
    };

    CreateGeometryY();
}

Esfera::Esfera(){

  float angle, coseno, seno;
  float r = RADIO;


  angle = 3*PI/2;

  for (int i= 0; i < DEFAULT_CUT; i++){
      coseno = cos(angle); seno = sin(angle);
      Vertices.push_back({r/2*coseno,r/2*seno,0.0});
      angle =(angle + ( PI / DEFAULT_CUT));
    }

  Vertices.push_back({r/2*cos(PI/2),r/2*sin(PI/2),0.0});

  CreateGeometryY();
}

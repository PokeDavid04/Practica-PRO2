/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

//CONSTRUCTORAS

Proceso::Proceso(){
    identificador = -1;
    memoria = -1;
    tiempo = -1;
    prioridad = PRIORIDAD_VACIA;
}

Proceso::Proceso(int id, int cmem, int t, string p){
    identificador = id;
    memoria = cmem;
    tiempo = t;
    prioridad = p;
}

Proceso::Proceso(int cmem){
    identificador = -1;
    memoria = cmem;
    tiempo = -1;
    prioridad = PRIORIDAD_VACIA;
}


//MODIFICADORAS

void Proceso::avanzar_tiempo(int t){
    if(tiempo >= t) tiempo -=t;
    else tiempo = 0;
}

//CONSULTORAS

int Proceso::consul_identificador() const{
    return identificador;
}

int Proceso::consul_memoria() const{
    return memoria;
}

int Proceso::consul_tiempo() const{
    return tiempo;
}

string Proceso::consul_prioridad() const{
    return prioridad;
}


//LECTURA Y ESCRITURA

void Proceso::escribir() const{
    cout << identificador << " " << memoria << " " << tiempo;
}
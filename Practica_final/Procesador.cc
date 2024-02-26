/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

//CONSTRUCTORAS

Procesador::Procesador(){
    identificador = IDENTIFICADOR_VACIO;
    cmemlibre = 0;
}

Procesador::Procesador(string id, int cmem){
    identificador = id;
    cmemlibre = cmem;

    //Crea la lista con un solo elemento (vacio) que sea un Procesador vacio con cant de memoria cmem (la total del procesador)
    memprocesos.push_back(Proceso(cmem));
    
}


//MODIFICADORAS

void Procesador::avanzar_tiempo(int t){
    map<int,list<Proceso>::iterator>::iterator it2 = mapprocesos.begin();
    while(it2 != mapprocesos.end()){
        list<Proceso>::iterator it = it2->second;
        (*it).avanzar_tiempo(t);

        if((*it).consul_tiempo() == 0){ //Comprueva si ha llegado a 0 para eliminarlo (convertirlo en hueco)
            //Si justo despues o justo antes habia un hueco hay que juntarlos
            int suma = (*it).consul_memoria();
            cmemlibre += suma;
            if(it != memprocesos.begin()){ //Tiene un elemento a la izquierda (borrarlo si es hueco)
                --it;
                list<Proceso>::iterator it_izq = it;
                ++it;
                if((*it_izq).consul_identificador() == -1){
                    suma += (*it_izq).consul_memoria();
                    memprocesos.erase(it_izq); 
                }
            }
            if(it != --memprocesos.end()){ //Tiene uno a la derecha (borrarlo si es hueco)
                ++it;
                list<Proceso>::iterator it_der = it;
                --it;
                if((*it_der).consul_identificador() == -1){
                    suma += (*it_der).consul_memoria();
                    memprocesos.erase(it_der); 
                }
            }
            (*it) = Proceso(suma);
            it2 = mapprocesos.erase(it2);
        }
        else ++it2;
    }
}

int Procesador::anadir_proceso(const Proceso &p){
    //comprovar si existe el proceso
    int id = p.consul_identificador();
    map<int,list<Proceso>::iterator>::iterator it = mapprocesos.find(id);
    if(it != mapprocesos.end()) return 1; //Si ya existe el proceso devuelve 1
    
    //Comprovar si la memoria que ocupa el proceso es mas grande que la memoria libre
    int mem = p.consul_memoria();
    if(mem > cmemlibre) return 2; //Si no cabe el proceso devuelve 2
    
    list<Proceso>::iterator it2 = memprocesos.begin();
    list<Proceso>::iterator itmejor;
    bool primerhueco = false;
    int mejormem;
    int sinconsultar = cmemlibre; //Memoria libre del procesador que queda por consultar

    while(it2 != memprocesos.end() && !primerhueco && sinconsultar >= mem){ //Busca el primer hueco donde cabe
        if((*it2).consul_identificador() == -1){
            if((*it2).consul_memoria() >= mem) primerhueco = true;
            sinconsultar -= (*it2).consul_memoria();
        } 
        if(!primerhueco) ++it2;
    }
    if(!primerhueco) return 2; //Devuelve que no ha encontrado ningun hueco (no cabe)
    
    itmejor = it2;
    mejormem = (*itmejor).consul_memoria();
    ++it2;
    
    while(it2!=memprocesos.end() && mejormem > mem && sinconsultar >= mem){ //Compara los siguientes huecos hasta que encuantre el mejor o no haya mas
        if((*it2).consul_identificador() == -1){
            if((*it2).consul_memoria() >= mem && (*it2).consul_memoria() < mejormem){
                itmejor = it2;
                mejormem = (*itmejor).consul_memoria();
            }
            sinconsultar -= (*it2).consul_memoria();
        }
        ++it2;
    }

    //Si el hueco es del mismo tamaño que el proceso, lo sustituye
    if(mejormem == mem){
        cmemlibre -= mem;
        (*itmejor) = p;
        mapprocesos.insert(make_pair(id, itmejor));
    }
    //Si el hueco es mas grande deja el hueco sobrante a su derecha
    else if(mejormem > mem){
        cmemlibre -= mem;
        (*itmejor) = p;
        mapprocesos.insert(make_pair(id, itmejor));
        ++itmejor;
        memprocesos.insert(itmejor, Proceso(mejormem - mem));
    }
    return 0;
}

int Procesador::eliminar_proceso_identificador(int id){
    //comprobar si existe el proceso
    map<int,list<Proceso>::iterator>::iterator it2 = mapprocesos.find(id);
    if(it2 == mapprocesos.end()) return 1; //Devuelve que no existe el proceso

    list<Proceso>::iterator it = it2->second;

    int suma = (*it).consul_memoria();
    cmemlibre += suma;
    if(it != memprocesos.begin()){ //Tiene un elemento a la izquierda (borrarlo si es hueco)
        --it;
        list<Proceso>::iterator it_izq = it;
        ++it;
        if((*it_izq).consul_identificador() == -1){
            suma += (*it_izq).consul_memoria();
            memprocesos.erase(it_izq); 
        }
    }
    if(it != --memprocesos.end()){ //Tiene uno a la derecha (borrarlo si es hueco)
        ++it;
        list<Proceso>::iterator it_der = it;
        --it;
        if((*it_der).consul_identificador() == -1){
            suma += (*it_der).consul_memoria();
            memprocesos.erase(it_der); 
        }   
    }
    (*it) = Proceso(suma);
    mapprocesos.erase(it2);
    return 0;
}

void Procesador::compactar_memoria(){
    list<Proceso>::iterator it = memprocesos.begin();
    int suma = 0;
    while(it != memprocesos.end()){
        if((*it).consul_identificador() == -1){
            suma += (*it).consul_memoria();
            it = memprocesos.erase(it);
        }
        else ++it;
    }
    memprocesos.push_back(Proceso(suma));
}

//CONSULTORAS

pair<int, int> Procesador::consul_cabe_hueco(int mem, int id, bool& valid){
    valid = true; //Hasta que se demuestre lo contrario
    
    //Comprovar si existe el proceso
    map<int,list<Proceso>::iterator>::iterator it2 = mapprocesos.find(id);
    if(it2 != mapprocesos.end()){
        valid = false;
        return make_pair(-1, -1);
    }
    
    //Comprovar si la memoria que ocupa el proceso es mas grande que la memoria libre
    if(mem > cmemlibre){
        valid = false;
        return make_pair(-1, -1);
    }


    list<Proceso>::iterator it = memprocesos.begin();
    list<Proceso>::iterator itmejor;
    int mejormem;
    bool primerhueco = false;
    int sinconsultar = cmemlibre; //Memoria libre del procesador que queda por consultar

    while(it!=memprocesos.end() && !primerhueco && sinconsultar >= mem){ //Busca el primer hueco donde cabe
        if((*it).consul_identificador() == -1){
            if((*it).consul_memoria() >= mem) primerhueco = true;
            sinconsultar -= (*it).consul_memoria();
        } 
        if(!primerhueco) ++it;
    }
    if(!primerhueco){ //No ha encontrado ningun hueco (no cabe)
        valid = false;
        return make_pair(-1, -1);
    }

    itmejor = it;
    mejormem = (*itmejor).consul_memoria();
    ++it;
    
    while(it!=memprocesos.end() && mejormem > mem && sinconsultar >= mem){ //Compara los siguientes huecos hasta que encuantre el mejor o no haya mas
        if((*it).consul_identificador() == -1){
            if((*it).consul_memoria() >= mem && (*it).consul_memoria() < mejormem){
                itmejor = it;
                mejormem = (*itmejor).consul_memoria();
            }
            sinconsultar -= (*it).consul_memoria();
        }
        ++it;
    }
    
    return make_pair(mejormem, cmemlibre - mem);
}

bool Procesador::tiene_procesos() const{
    return !mapprocesos.empty();
}


//LECTURA Y ESCRITURA

void Procesador::escribir() const{
    list<Proceso>::const_iterator it = memprocesos.cbegin();
    int suma = 0;
    while(it != memprocesos.cend()){
        if((*it).consul_identificador() != -1){
            cout << suma << " ";
            (*it).escribir();
            cout << endl;
        } 
        suma += (*it).consul_memoria();
        ++it;
    }
}
/** @file AreaProcesos.cc
    @brief Código de la clase AreaProcesos
*/

#include "AreaProcesos.hh"

//CONSTRUCTORAS

AreaProcesos::AreaProcesos(){

}

//MODIFICADORAS

void AreaProcesos::anadir_prioridad(string p){
    map<string,info_prioridad>::iterator it = prioridades.find(p);
    if(it != prioridades.end()) cout << "error: ya existe prioridad" << endl;
    else{
        info_prioridad inf;
        inf.rechazos = 0;
        inf.enviados = 0;
        prioridades.insert(make_pair(p, inf));
    }
}

void AreaProcesos::eliminar_prioridad(string p){
    map<string,info_prioridad>::iterator it = prioridades.find(p);
    if(it == prioridades.end()) cout << "error: no existe prioridad" << endl;
    else if(!(it->second).listprocesos.empty()) cout << "error: prioridad con procesos" << endl;
    else prioridades.erase(it);
}

void AreaProcesos::anadir_proceso(const Proceso &p){
    string prio = p.consul_prioridad();
    int id = p.consul_identificador();
    map<string,info_prioridad>::iterator it = prioridades.find(prio);
    if(it == prioridades.end()) cout << "error: no existe prioridad" << endl; //comprueba si no existe la prioridad
    else{
        list<Proceso>::iterator it2 = (it->second).listprocesos.begin();
        bool error = false;
        while(it2 != (it->second).listprocesos.end() && !error){ //comprueba si existe el proceso en la prioridad
            if((*it2).consul_identificador() == id) error = true;
            ++it2;
        }
        if(error) cout << "error: ya existe proceso" << endl;
        else (it->second).listprocesos.push_back(p);
    }
}

void AreaProcesos::anadir_proceso_rechazado(const Proceso &p){
    string prio = p.consul_prioridad();
    map<string,info_prioridad>::iterator it = prioridades.find(prio);
    (it->second).listprocesos.push_back(p);
    (it->second).rechazos += 1;
}

Proceso AreaProcesos::sacar_primer_proceso(){
    map<string,info_prioridad>::iterator it = prioridades.begin();
    while(it != prioridades.end()){
        if(!(it->second).listprocesos.empty()){
            list<Proceso>::iterator it2 = (it->second).listprocesos.begin();
            Proceso paux = *it2;
            (it->second).listprocesos.erase(it2);
            return paux;
        }
        ++it;
    }
    return Proceso();
}

void AreaProcesos::aumenta_unidad_enviados_prioridad(string p){
    map<string,info_prioridad>::iterator it = prioridades.find(p);
    (it->second).enviados += 1;
}

// CONSULTORAS


//LECTURA Y ESCRITURA

void AreaProcesos::leer(){
    int n;
    cin >> n;
    info_prioridad info;
    info.rechazos = 0;
    info.enviados = 0;
    for(int i=0; i<n; ++i){
        string p;
        cin >> p;
        prioridades.insert(make_pair(p, info));
    }
}


void AreaProcesos::escribir(){
    map<string, info_prioridad>::iterator it1 = prioridades.begin();
    while(it1 != prioridades.end()){
        cout << it1->first << endl;
        if(!(it1->second).listprocesos.empty()){
            list<Proceso>::iterator it2 = (it1->second).listprocesos.begin();
            while(it2 != (it1->second).listprocesos.end()){
                (*it2).escribir();
                cout << endl;
                ++it2;
            }
        }
        cout << it1->second.enviados << " " << it1->second.rechazos << endl;
        ++it1;
    }
}

void AreaProcesos::escribir_prioridad(string prio) const{
    map<string, info_prioridad>::const_iterator it = prioridades.find(prio);
    if(it == prioridades.end()) cout << "error: no existe prioridad" << endl;
    else{
        for(list<Proceso>::const_iterator it2 = it->second.listprocesos.begin(); it2 != it->second.listprocesos.end(); ++it2){
            (*it2).escribir();
            cout << endl;
        }
        cout << it->second.enviados << " " << it->second.rechazos << endl;
    }
}










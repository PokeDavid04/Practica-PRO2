/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

//CONSTRUCTORAS

Cluster::Cluster(){
    
}


//MODIFICADORAS

void Cluster::anadir_proceso_procesador(string id, const Proceso &p){
    map<string, Procesador>::iterator it = listprocesadores.find(id);
    if(it == listprocesadores.end()) cout << "error: no existe procesador" << endl;
    else {
        int x = it->second.anadir_proceso(p);
        if(x == 1) cout << "error: ya existe proceso" << endl;
        else if(x == 2) cout << "error: no cabe proceso" << endl;
    }
}

void Cluster::eliminar_proceso_procesador(string id, int iid){
    map<string, Procesador>::iterator it = listprocesadores.find(id);
    if(it == listprocesadores.end()) cout << "error: no existe procesador" << endl;
    else {
        int x = it->second.eliminar_proceso_identificador(iid);
        if(x == 1) cout << "error: no existe proceso" << endl;
    }
}

void Cluster::avanzar_tiempo(int t){
    map<string, Procesador>::iterator it = listprocesadores.begin();
    while (it != listprocesadores.end()){
        it->second.avanzar_tiempo(t);
        ++it;
    }
}

void Cluster::i_copiar_cluster(BinTree<pair<string, int>>& c, string id, const BinTree<pair<string, int>>& cn, bool& valid){
    if(!c.empty()){
        if(c.value().first == id){
            if(c.left().empty() && c.right().empty()) c = cn;
            else{
                valid = false;
            } 
        }
        else{
            BinTree<pair<string, int>> l = c.left();
            BinTree<pair<string, int>> r = c.right();
            i_copiar_cluster(l, id, cn, valid);
            i_copiar_cluster(r, id, cn, valid);
            c = BinTree<pair<string, int>>(c.value(), l, r);
        }
    }
}

void Cluster::anadir_cluster(string id, Cluster& c){
    map<string, Procesador> aux = c.listprocesadores;
    map<string, Procesador>::iterator it = listprocesadores.find(id);
    if(it == listprocesadores.end()) cout << "error: no existe procesador" << endl;
    else if(it->second.tiene_procesos()){
        cout << "error: procesador con procesos" << endl;
    }
    else{
        bool valid = true;
        i_copiar_cluster(clust, id, c.clust, valid);
        if(valid){
            listprocesadores.erase(it);
            it = aux.begin();
            while(it != aux.end()){
                listprocesadores.insert(make_pair(it->first, it->second));
                ++it;
            }
        }
        else cout << "error: procesador con auxiliares" << endl;
        
    }
}

string Cluster::consul_mejor_hueco(const BinTree<pair<string, int>>& a, int cmem, int idproc) {
	string mejorid = "no_cabe";
	pair<int, int> mejorinfo(-1, -1); //first = tamaño del hueco mas ajustado; second = memoria que quedaria libre al anadir el proceso
	bool valido = false;
	bool primero=true;
	
		
	if (!a.empty()) {
		queue< BinTree<pair<string, int>> > c;
		c.push(a);
		while (!c.empty()) {
			string id = (c.front().value()).first;
			map<string, Procesador>::iterator it = listprocesadores.find(id);
			pair<int, int> i = (it->second).consul_cabe_hueco(cmem, idproc, valido);
			if(valido){
				if(primero){ //Si es el primer hueco que encuetra es el mejor de momento
					mejorid = id;
					mejorinfo = i;
                    primero = false;
				}
				else{ //Si encontramos otro hay que compararlos
					if(mejorinfo.first > i.first){ //Compara si el tamaño del hueco es mas pequeño que el mejor anterior
						mejorid = id;
						mejorinfo = i;
					}
					else if(mejorinfo.first == i.first){ //Si son iguales comparar si la posicion del heuco es menor a la mejor anterior
						if(mejorinfo.second < i.second){
                            mejorid = id;
							mejorinfo = i;
                        }
					}
				}
			}
			if (not c.front().left().empty()) c.push(c.front().left());
			if (not c.front().right().empty()) c.push(c.front().right());
			c.pop();
		}
	}
	return mejorid;
}

bool Cluster::anadir_proceso(const Proceso &p){
    string id = consul_mejor_hueco(clust, p.consul_memoria(), p.consul_identificador());
    if(id == "no_cabe") return false;
    else{
        map<string, Procesador>::iterator it = listprocesadores.find(id);
        (it->second).anadir_proceso(p);
        return true;
    }
    
}

void Cluster::compactar_memoria_procesador(string id){
    map<string, Procesador>::iterator it = listprocesadores.find(id);
    if(it == listprocesadores.end()) cout << "error: no existe procesador" << endl;
    else (it->second).compactar_memoria();
}

void Cluster::compactar_memoria(){
    for(map<string, Procesador>::iterator it = listprocesadores.begin(); it != listprocesadores.end(); ++it){
        (it->second).compactar_memoria();
    }
}

//CONSULTORAS


//LECTURA Y ESCRITURA

BinTree<pair<string, int>> Cluster::i_leer(){
    string id; cin >> id;

    if(id == "*") return BinTree<pair<string, int>>();
    else{
        int cmem; cin >> cmem;
        //Crear procesador y añadirlo al map
        Procesador paux(id, cmem);
        listprocesadores.insert(make_pair(id,paux));

        pair<string, int> par(id, cmem);

        BinTree<pair<string, int>> arbolizquierda = i_leer();
        BinTree<pair<string, int>> arbolderecha = i_leer();
        return BinTree<pair<string, int>>(par, arbolizquierda, arbolderecha);
    }
}

void Cluster::leer(){
    listprocesadores.clear();
    clust = i_leer();
}

void Cluster::escribir(){
    for(map<string,Procesador>::const_iterator it = listprocesadores.cbegin(); it != listprocesadores.cend(); ++it){
        cout << it->first << endl;
        (it->second).escribir();
    }
}

void Cluster::i_escribir_estructura(const BinTree<pair<string,int>>& c){
    if(c.empty()){
        cout << " ";
    }
    else{
        cout << "(" << (c.value()).first;
        i_escribir_estructura(c.left());
        i_escribir_estructura(c.right());
        cout << ")";
    }
}

void Cluster::escribir_estructura(){
    i_escribir_estructura(clust);
    cout << endl;
}

void Cluster::escribir_procesador(string id){
    map<string, Procesador>::iterator it = listprocesadores.find(id);
    if(it == listprocesadores.end()) cout << "error: no existe procesador" << endl;
    else it->second.escribir();
}

// #ifndef NO_DIAGRAM
#include "Proceso.hh"
#include "Procesador.hh"
#include "Cluster.hh"
#include "AreaProcesos.hh"
using namespace std;
// #endif

int main(){
    //inicializa un cluster
    Cluster c;
    c.leer();

    //inicializa un area de procesos pendientes
    AreaProcesos area;
    area.leer();

    //lee comando
    string com;
    cin >> com;

    while(com != "fin"){
        //procesa comando
        if(com == "configurar_cluster" || com == "cc"){
            c.leer();
            cout << "#" << com << endl;
        }
        else if(com == "modificar_cluster" || com == "mc"){
            string p; cin >> p;
            Cluster c2; c2.leer();
            cout << "#" << com << " " << p << endl;
            c.anadir_cluster(p, c2);
        }
        else if(com == "alta_prioridad" || com == "ap"){
            string p; cin >> p;
            cout << "#" << com << " " << p << endl;
            area.anadir_prioridad(p);
        }
        else if(com == "baja_prioridad" || com == "bp"){
            string p; cin >> p;
            cout << "#" << com << " " << p << endl;
            area.eliminar_prioridad(p);
        }
        else if(com == "alta_proceso_espera" || com == "ape"){
            string prio;
            int id, cmem, t;
            cin >> prio >> id >> cmem >> t;
            Proceso pro(id, cmem, t, prio);
            cout << "#" << com << " " << prio << " " << id << endl;
            area.anadir_proceso(pro);
        }
        else if(com == "alta_proceso_procesador" || com == "app"){
            string id; cin >> id;
            int id2, mem, t;
            cin >> id2 >> mem >> t;
            cout << "#" << com << " " << id << " " << id2 << endl;
            string prioridad = "sin_prioridad";
            Proceso p(id2, mem, t, prioridad);
            c.anadir_proceso_procesador(id, p);
        }
        else if(com == "baja_proceso_procesador" || com == "bpp"){ 
            string id; int iid; cin >> id >> iid;
            cout << "#" << com << " " << id << " " << iid << endl;
            c.eliminar_proceso_procesador(id, iid);
            
        }
        else if(com == "enviar_procesos_cluster" || com == "epc"){ 
            int n; cin >> n; 
            cout << "#" << com << " " << n << endl;
            Proceso p;
            list<Proceso> procesosrechazados;
            bool acabado = false;
            while(n>0 && !acabado){ //Intenta añadir n procesos hasta que los ha añadido todos o no queda ninguno en el area de espera
                p = area.sacar_primer_proceso();
                if(p.consul_identificador() == -1) acabado = true;
                else{
                    bool anadido = c.anadir_proceso(p);
                    if(anadido){
                        area.aumenta_unidad_enviados_prioridad(p.consul_prioridad());
                        --n;
                    } 
                    else{
                        procesosrechazados.push_back(p);
                    }
                }
            }
            list<Proceso>::iterator it = procesosrechazados.begin();
            while(it != procesosrechazados.end()){ //Devuelve los procesos rechazados al area de espera
                area.anadir_proceso_rechazado(*it);
                ++it;
            }
        }
        else if(com == "avanzar_tiempo" || com == "at"){
            int t; cin >> t;
            cout << "#" << com << " " << t << endl;
            c.avanzar_tiempo(t);
        }
        else if(com == "imprimir_prioridad" || com == "ipri"){
            string prio; cin >> prio;
            cout << "#" << com << " " << prio << endl;
            area.escribir_prioridad(prio);
        }
        else if(com == "imprimir_area_espera" || com == "iae"){
            cout << "#" << com << endl;
            area.escribir();
        }
        else if(com == "imprimir_procesador" || com == "ipro"){
            string id; cin >> id;
            cout << "#" << com << " " << id << endl;
            c.escribir_procesador(id);
        }
        else if(com == "imprimir_procesadores_cluster" || com == "ipc"){
            cout << "#" << com << endl;
            c.escribir();
        }
        else if(com == "imprimir_estructura_cluster" || com == "iec"){
            cout << "#" << com << endl;
            c.escribir_estructura();
        }
        else if(com == "compactar_memoria_procesador" || com == "cmp"){
            string id; cin >> id;
            cout << "#" << com  << " " << id << endl;
            c.compactar_memoria_procesador(id);
        }
        else if(com == "compactar_memoria_cluster" || com == "cmc"){
            cout << "#" << com << endl;
            c.compactar_memoria();
        }
        //lee comando
        cin >> com;
    }
}

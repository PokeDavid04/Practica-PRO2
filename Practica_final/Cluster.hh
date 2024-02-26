/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

// #ifndef NO_DIAGRAM
#include "Procesador.hh"
#include "BinTree.hh"
#include <queue>
using namespace std;
// #endif

/** @class Cluster
    @brief Representa un cluster con la estructura en forma de arbol i sus correspondientes procesadores agrupados en un diccionario con su identificador como "key"

*/

class Cluster
{
public:
  //Constructoras
    /**
     * @name Constructoras
     * @{
    */

  /** @brief Creadora por defecto

      Se ejecuta automáticamente al declarar un cluster
      \pre <em>cierto</em>
      \post El resultado es un cluster vacio
  */
  Cluster();
  /**@}*/



  //Modificadoras
  /**
     * @name Modificadoras
     * @{
    */

  /** @brief Intenta añadir un cluster en el lugar de un procesador

      \pre <em>cierto</em>
      \post El parámetro implícito pasa a tener el cluster leido en lugar del procesador con el identificador id si existe el procesador y no tiene procesadores auxiliares
  */
  void anadir_cluster(string id, Cluster& c);

  /** @brief Intenta un proceso en un procesador concreto del parámetro implícito

      \pre <em>cierto</em>
      \post El parámetro implícito tiene el proceso p en el procesador con identificador id si existe id, no existe previamente el proceso en el procesador y cabe, de lo contrario imprime un error
  */
  void anadir_proceso_procesador(string id, const Proceso &p);

  /** @brief Intenta eliminar un proceso en un procesador concreto del parámetro implícito

      \pre <em>cierto</em>
      \post El parámetro implícito ya no tiene el proceso con identificador iid en el procesador con identificador id si existen ambos, de lo contrario imprime un error
  */
  void eliminar_proceso_procesador(string id, int iid);

  /** @brief Intenta añadir un proceso al parámetro implícito

      Añade p en el procesador con el hueco que más se ajuste a la memoria que ocupa p, en caso de empate lo añade al que tenga mas memoria libre, en caso de empate, lo añade al más próximo a la raíz y en caso de empate al de más a la izquierda.
      \pre <em>cierto</em>
      \post El parámetro implícito tiene el proceso p en algún procesador si cabe y devuelve true, si no devuelve false
  */
  bool anadir_proceso(const Proceso &p);

  /** @brief Modificadora de los procesos de los procesadores del parámetro implícito

      \pre <em>cierto</em>
      \post Avanza t unidades de tiempo en los procesos de cada procesador del parámetro implícito y elimina los procesos terminados
  */
  void avanzar_tiempo(int t);

  /** @brief Modificadora de los procesos de un procesador del parámetro implicito

      Reordena los procesos de un procesador por orden de llegada, lo mas a la izquierda posible y sin dejar huecos entre medio
      \pre <em>cierto</em>
      \post Reordena los procesos del procesador con identificador id del parámetro implícito
  */
  void compactar_memoria_procesador(string id);

  /** @brief Modificadora de los procesos de cada procesador del parámetro implicito

      Reordena los procesos de cada procesador por orden de llegada, lo mas a la izquierda posible y sin dejar huecos entre medio
      \pre <em>cierto</em>
      \post Reordena los procesos de cada procesador del parámetro implícito
  */
  void compactar_memoria();
  /**@}*/



  //Consultoras
  /**
     * @name Consultoras
     * @{
    */

  /**@}*/



  /**
     * @name Lectura y Escritura
     * @{
    */
  //Lectura de cluster

  /** @brief Operación de lectura

      \pre <em>cierto</em>
      \post Se han leido los atributos del parámetro implícito desde el canal standard de entrada
  */
  void leer();


  //Escritura de cluster

  /** @brief Operación de escritura

      \pre <em>cierto</em>
      \post Se han escrito los atributos del parámetro implícito en el canal standard de salida
  */
  void escribir();

  /** @brief Operación de escritura de estructura

      \pre <em>cierto</em>
      \post Se han escrito la estructura del parámetro implícito en el canal standard de salida
  */
  void escribir_estructura();

  /** @brief Operación de escritura de un procesador concreto

      \pre <em>cierto</em>
      \post Se ha escrito, si existe, el procesador con identificador id del parámetro implícito en el canal standard de salida
  */
  void escribir_procesador(string id);
  /**@}*/

private:
BinTree<pair<string, int>> clust;
map<string, Procesador> listprocesadores;

  /** @brief Operación auxiliar de lectura

      \pre <em>cierto</em>
      \post Se han leido los atributos del parámetro implícito desde el canal standard de entrada y devuelve un cluster auxiliar
  */
  BinTree<pair<string,int>> i_leer();

  /** @brief Operación auxiliar de escritura de estructura
      \pre <em>cierto</em>
      \post Se han escrito la estructura del parámetro implícito en el canal standard de salida
  */
  void i_escribir_estructura(const BinTree<pair<string,int>>& c);

  /** @brief Copia un cluster y sustituye el procesador del identificador id por el cluster cn

      \pre Existe el procesador con identificador id
      \post El parámetro implícito pasa a tener el cluster leido en lugar del procesador con el identificador id si no tiene procesos en ejecucion, si no cambia valid a false
  */
  void i_copiar_cluster(BinTree<pair<string, int>>& c, string id, const BinTree<pair<string, int>>& cn, bool& valid);
  
  /** @brief Devuelve el mejor procesador donde cabe un procesos con cmem cantidad de memoria

      \pre cmem es la cantidad de memoria que ocupa un procesador que metemos al cluster
      \post Devuelve el identificador del procesador con el hueco mas ajustado
  */
  string consul_mejor_hueco(const BinTree<pair<string, int>>& a, int cmem, int idproc);
};



#endif

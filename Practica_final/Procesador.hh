/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

// #ifndef NO_DIAGRAM
#include "Proceso.hh"
#include <map>
using namespace std;
// #endif

/** @class Procesador
    @brief Representa un procesador con un identificador, una cantidad de memoria libre, una lista con los procesos activos en la memoria y un map con los identificadores de los procesos como "key" y un iterador apuntando a ellos

*/

class Procesador
{
public:
  //Constructoras
    /**
     * @name Constructoras
     * @{
    */

  /** @brief Creadora por defecto

      Se ejecuta automáticamente al declarar un procesador
      \pre <em>cierto</em>
      \post El resultado es un procesador sin identificador, sin cantidad de memoria ni procesos activos 
  */
  Procesador();

  /** @brief Creadora con valores concretos

      \pre id un string de letras y dígitos, cmem>0
      \post El resultado es un procesador con identificador "id", cantidad de memoria "cmem" y sin procesos activos
  */
  Procesador(string id, int cmem);
  /**@}*/



  //Modificadoras
  /**
     * @name Modificadoras
     * @{
    */

  /** @brief Modificadora del tiempo de los procesos del parámetro implícito

      \pre <em>cierto</em>
      \post Avanza t unidades de tiempo en los procesos de la lista de procesos del parámetro implícito y elimina los procesos terminados (cuando su tiempo es igual a 0) y actualiza la memoria libre
  */
  void avanzar_tiempo(int t);

  /** @brief Modificadora de la memoria del parámetro implícito

      Reordena los procesos por orden de llegada, lo mas a la izquierda posible y sin dejar huecos entre medio, solo uno a la izquierda del todo que ocupa el total de memoria libre
      \pre <em>cierto</em>
      \post Reordena los procesos de la lista de procesos del parámetro implícito
  */
  void compactar_memoria();

/** @brief Intenta añadir un proceso al procesador

      \pre <em>cierto</em>
      \post Si p existe o no cabe devuele 1 o 2 (errores), de lo contrario añade p a la memoria en el hueco mas ajustado posible y en caso de empate el de mas a la izquierda, y devuelve un 0 y actualiza la cantidad memoria libre
  */
  int anadir_proceso(const Proceso &p);

/** @brief Modificadora de la memoria del parámetro implícito

      \pre <em>cierto</em>
      \post Si no existe el proceso devuelve 1 (error), de lo contrario lo elimina de la memoria y actualiza la cantidad memoria libre
  */
  int eliminar_proceso_identificador(int id);
  /**@}*/



  //Consultoras
  /**
     * @name Consultoras
     * @{
    */

  /** @brief Consulta si tiene procesos

      \pre <em>cierto</em>
      \post El resultado es true si el parámetro implícito tiene procesos en ejecución y false de lo contrario
  */
  bool tiene_procesos() const;

  /** @brief Operación que comprueba si cabe un proceso

      \pre <em>cierto</em>
      \post Devuelve la posicion del hueco mas ajustado y la memoria libre que dejaria al anadirlo, a demas determina valid segun se encuentre el proceso en el procesador o no se pueda añadir, entonces lo combierte en false
  */
  pair<int, int> consul_cabe_hueco(int mem, int id, bool& valid);
  /**@}*/


  /**
     * @name Lectura y Escritura
     * @{
    */

  //Escritura procesador

  /** @brief Operación de escritura

      \pre <em>cierto</em>
      \post Se han escrito los atributos del parámetro implícito en el canal standard de salida
  */
  void escribir() const;
  /**@}*/

private:
  string identificador;
  static constexpr const char* IDENTIFICADOR_VACIO = "sin_identificador";
  int cmemlibre;
  list<Proceso> memprocesos;
  map<int, list<Proceso>::iterator> mapprocesos;
};

#endif

/** @file AreaProcesos.hh
    @brief Especificación de la clase Area de Procesos
*/

#ifndef _AREA_PROCESOS_HH_
#define _AREA_PROCESOS_HH_

// #ifndef NO_DIAGRAM
#include "Proceso.hh"
#include <map>
#include <utility>
using namespace std;
// #endif

/** @class AreaProcesos
    @brief Representa un área de procesos con un diccionario de prioridades, ordenadas de mayor a menor prioridad. Para cada prioridad encontramos una lista de procesos ordenadas de mas antiguo a mas reciente, y sus respectivos numeros de rechazos y de enviados
    
*/

class AreaProcesos
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
      \post El resultado es un área de procesos vacia
  */
  AreaProcesos();
  /**@}*/

  //Modificadoras
  /**
     * @name Modificadoras
     * @{
    */

  /** @brief Intenta añadir un proceso al área de procesos

      \pre <em>cierto</em>
      \post Si no existia ese proceso previamente el parámetro implícito pasa a tener un proceso más en la lista de procesos de su prioridad, en caso contrario imprime un error
  */
  void anadir_proceso(const Proceso &p);

  /** @brief Añade un proceso al área de procesos, rechazado préviamente por el cluster

      \pre No hay ningún proceso en la lista de su prioridad con el identificador
      \post El parámetro implícito pasa a tener un proceso más en la lista de procesos de su prioridad y el numero de rechazos de la prioridad de p aumenta en 1
  */
  void anadir_proceso_rechazado(const Proceso &p);

  /** @brief Intenta añadir una prioridad al área de procesos

      \pre <em>cierto</em>
      \post El parámetro implícito pasa a tener una prioridad más en el map de prioridades, sus correspondientes rechazos y enviados son 0 y lista de procesos vacia si no existia la prioridad, en caso contrario imprime un error
  */
  void anadir_prioridad(string p);

  /** @brief Intenta eliminar una prioridad del área de procesos

      \pre <em>cierto</em>
      \post El parámetro implícito pasa a no tener la prioridad p en el map de prioridades si existia la prioridad i no tiene procesos, en caso contrario imprime un error
  */
  void eliminar_prioridad(string p);

  /** @brief Elimina y devuelve el primer proceso de la maxima prioridad del Area de Procesos

      \pre <em>cierto</em>
      \post Si existe algún proceso, el parámetro implícito pasa a tener un proceso menos en la lista de procesos de la maxima prioridad posible, si no devuelve un Proceso vacio
  */
  Proceso sacar_primer_proceso();

  /** @brief Aumenta en una unidad los procesos enviados

      \pre <em>cierto</em>
      \post El parámetro implícito pasa tener un proceso enviado más de la prioridad de p
  */
  void aumenta_unidad_enviados_prioridad(string p);
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
  //Lectura de área de procesos

  /** @brief Operación de lectura

      \pre <em>cierto</em>
      \post Se han leido los atributos del parámetro implícito desde el canal standard de entrada
  */
  void leer();


  //Escritura de área de procesos

  /** @brief Operación de escritura

      \pre <em>cierto</em>
      \post Se han escrito los atributos del parámetro implícito en el canal standard de salida por orden decreciente de prioridad
  */
  void escribir();

  /** @brief Operación de escritura de la prioridad

      \pre <em>cierto</em>
      \post Se han escrito los procesos de la prioridad y sus numeros de rechazos y enviados
  */
  void escribir_prioridad(string prio) const;
  /**@}*/

private:
  struct info_prioridad {
    list<Proceso> listprocesos;
    int rechazos;
    int enviados;
  };
  map<string, info_prioridad> prioridades;
};

#endif

/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef _PROCESO_HH_
#define _PROCESO_HH_

// #ifndef NO_DIAGRAM
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
// #endif

/** @class Proceso
    @brief Representa un proceso con identificador, cantidad de memoria que ocupa, tiempo de ejecución y prioridad

*/
class Proceso
{
public:
  //Constructoras
    /**
     * @name Constructoras
     * @{
    */

  /** @brief Creadora por defecto

      Se ejecuta automáticamente al declarar un proceso
      \pre <em>cierto</em>
      \post El resultado es un proceso sin identificador, cantidad de memoria, tiempo de ejecución ni prioridad
  */
  Proceso();

  /** @brief Creadora con valores concretos

      \pre id>=0, cmem>0, t>0 y p un string de letras y dígitos
      \post El resultado es un proceso con identificador "id", cantidad de memoria "cmem", tiempo "t" y prioridad "p"
  */
  Proceso(int id, int cmem, int t, string p);

  /** @brief Creadora de un Proceso hueco

      \pre cmem>0
      \post El resultado es un proceso con identificador -1, cantidad de memoria "cmem", tiempo -1 y prioridad vacia
  */
  Proceso(int cmem);
  /**@}*/



  //Modificadoras
  /**
     * @name Modificadoras
     * @{
    */

  /** @brief Modificadora del atributo tiempo

      \pre <em>cierto</em>
      \post El parámetro implícito pasa a tener tiempo -t (si el tiempo quedase negativo, se queda en 0)
  */
  void avanzar_tiempo(int t);
  /**@}*/



  //Consultoras
  /**
     * @name Consultoras
     * @{
    */

  /** @brief Consultora del identificador

      \pre <em>cierto</em>
      \post El resultado es el identificador del parámetro implícito
  */
  int consul_identificador() const;

  /** @brief Consultora de la cantidad de memoria
      \pre <em>cierto</em>
      \post El resultado es al memoria del parámetro implícito
  */
  int consul_memoria() const;

  /** @brief Consultora del tiempo de ejecución

      \pre <em>cierto</em>
      \post El resultado es el tiempo del parámetro implícito
  */
  int consul_tiempo() const;

  /** @brief Consultora de la prioridad

      \pre <em>cierto</em>
      \post El resultado es la prioridad del parámetro implícito
  */
  string consul_prioridad() const;
  /**@}*/



  /**
     * @name Lectura y Escritura
     * @{
    */


  //Escritura de proceso

  /** @brief Operación de escritura

      \pre <em>cierto</em>
      \post Se han escrito los atributos del parámetro implícito en el canal standard de salida
  */
  void escribir() const;
  /**@}*/

private:
  static constexpr const char* PRIORIDAD_VACIA = "sin_prioridad";

  int identificador;
  int memoria;
  int tiempo;
  string prioridad;
};

#endif

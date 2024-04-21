#ifndef INICIADOR_FINITO
#define INICIADOR_FINITO

#include "CLASE_IniciadorTareas.h"
#include "../../Utils/CLASE_Contador.h"
    /**
     * @brief Tarea que permite iniciar la ejecución de otra tarea, cada cierta
     *  cantidad de tiempo, una cantidad finita de veces.
     */
    class IniciadorFinito : public IniciadorTareas {
        private:
            /**
             * @brief El contador que almacena la cantidad de iniciaciones
             *  restantes.
             */
            Contador<size_t> contIteraciones;
        
        public:
            /**
             * @brief Construye un IniciadorFinito, con el tiempo entre
             *  iniciaciones, cantidad de iniciaciones, scheduler y tarea
             *  especificados.
             *
             * @param msEntreIniciaciones La cantidad de milisegundos entre
             *  una iniciación de tarea y la siguiente.
             * @param numIniciaciones La cantidad de iniciaciones a realizar.
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             * @param tarea La tarea especificada (que no debería ser nula).
             */
            IniciadorFinito(unsigned long msEntreIniciaciones, unsigned long numIniciaciones, Scheduler *planif, Task *tarea);
            
            /**
             * @brief Reinicia el contador de iteraciones.
             *
             * @returns @c true para indicar que la tarea debería permanecer
             *  habilitada.
             */
            bool OnEnable(void) override;

            /**
             * @brief Decrementa al contador de iteraciones en @c 1.
             *
             * @returns @c true si el valor de @c contIteraciones es @c 0,
             *  @c false en caso contrario.
             */
            bool deboFinalizar(void) override;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override;
    };
#endif

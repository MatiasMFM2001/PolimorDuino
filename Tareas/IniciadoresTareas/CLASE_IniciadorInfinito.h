#ifndef INICIADOR_INFINITO
#define INICIADOR_INFINITO

#include "CLASE_IniciadorTareas.h"
    /**
     * @brief Tarea que permite iniciar la ejecución de otra tarea, cada cierta
     *  cantidad de tiempo, una cantidad infinita de veces.
     */
    class IniciadorInfinito : public IniciadorTareas {
        public:
            /**
             * @brief Construye un IniciadorInfinito, con el tiempo entre
             *  iniciaciones, scheduler y tarea especificados.
             *
             * @param msEntreIniciaciones La cantidad de milisegundos entre
             *  una iniciación de tarea y la siguiente.
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             * @param tarea La tarea especificada (que no debería ser nula).
             */
            IniciadorInfinito(unsigned long msEntreIniciaciones, Scheduler *planif, Task *tarea);
            
            /**
             * @returns @c false para mantener la iniciación infinita.
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

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INICIADOR_INFINITO
#define INICIADOR_INFINITO

#include "CLASE_IniciadorTareas.h"
#include "../../Medidores/Condiciones/INTERFAZ_CondicionResultado.h"
    /**
     * @brief Tarea que permite iniciar la ejecución de otra tarea, cada cierta
     *  cantidad de tiempo, una cantidad infinita de veces (o, si se especificó
     *  una condición, mientras ésta sea falsa).
     */
    class IniciadorInfinito : public IniciadorTareas {
        private:
            CondicionResultado<> *condicionFin;
        
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
             * @param condicionFin La condición a verificar (que puede ser nula).
             */
            IniciadorInfinito(const char *nombre, unsigned long msEntreIniciaciones, Scheduler *planif, Task *tarea, CondicionResultado<> *condicionFin = nullptr);
            
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

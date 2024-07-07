/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INVOCADOR_FUNCION
#define INVOCADOR_FUNCION

#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"
    /**
     * @brief Tarea que permite ejecutar periódicamente una función callback.
     */
    class InvocadorFuncion : public Task {
        private:
            /** @brief Puntero a la función a ejectuar. */
            void (*callback)(void);
        
        public:
            /**
             * @brief Construye un InvocadorFuncion, con el tiempo de espera, la
             *  cantidad de llamados, el scheduler y la función especificados.
             * 
             * @param msEntreLlamados La cantidad mínima de milisegundos a
             *  esperar entre una invocación y la siguiente.
             * @param numLlamados La cantidad de llamados a realizar antes de
             *  finalizar la tarea.
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             * @param callback La función a invocar en cada iteración (que puede
             *  ser nula).
             * @param habilitar @c true para habilitar la tarea al construirla,
             *  @c false para el caso contrario.
             */
            InvocadorFuncion(long msEntreLlamados, long numLlamados, Scheduler *planif, void (*callback)(void), bool habilitar = false);
        
            /**
             * @brief Ejecuta la función callback.
             *
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override;
    };
#endif

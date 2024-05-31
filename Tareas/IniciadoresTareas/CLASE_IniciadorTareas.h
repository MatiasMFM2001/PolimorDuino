/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INICIADOR_TAREAS
#define INICIADOR_TAREAS

#include "../../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include <Printable.h>
#include <Print.h>
    /**
     * @brief Tarea que permite iniciar la ejecución de otra tarea, cada cierta
     *  cantidad de tiempo.
     */
    class IniciadorTareas : public Task, public Printable {
        private:
            /** @brief La tarea a iniciar periódicamente. */
            Task *tarea;
            const char *nombre;
        
        public:
            /**
             * @brief Construye un IniciadorTareas, con el tiempo entre
             *  iniciaciones, scheduler y tarea especificados.
             *
             * @param msEntreIniciaciones La cantidad de milisegundos entre
             *  una iniciación de tarea y la siguiente.
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             * @param tarea La tarea especificada (que no debería ser nula).
             */
            IniciadorTareas(const char *nombre, unsigned long msEntreIniciaciones, Scheduler *planif, Task *tarea);

            /**
             * @brief Si la tarea no estaba activada y @c deboFinalizar(),
             *  se deshabilita.
             *
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override;

            /**
             * @returns @c true si hay que dejar de iniciar la tarea, @c false
             *  en caso contrario.
             */
            virtual bool deboFinalizar(void) = 0;
    };
#endif

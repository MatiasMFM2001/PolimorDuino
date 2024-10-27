/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PULSABLE_TAREA
#define PULSABLE_TAREA

#include "../CLASE_Pulsable.h"
#include "../../../Inclusiones/InclusionTaskSchedulerDeclarations.h"
    /**
     * @brief Decorador que conoce a una tarea, pero no hace nada con ella (para
     *  que sus subclases sí la usen).
     */
    class PulsableTarea : public Pulsable {
        protected:
            /** @brief Puntero a la tarea. */
            Task *tarea;

        public:
            /**
             * @brief Construye un PulsableIniciador, con el estado inicial
             *  y la tarea especificados.
             *
             * @param estadoInicial @c true para iniciar el programa con
             *  el objeto decorado encendido, @c false para el caso contrario.
             */
            PulsableTarea(bool estadoInicial, Task *tarea);

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

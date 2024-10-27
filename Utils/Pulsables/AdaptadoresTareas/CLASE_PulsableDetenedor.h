/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PULSABLE_DETENEDOR
#define PULSABLE_DETENEDOR

#include "CLASE_PulsableTarea.h"
#include "../../../Inclusiones/InclusionTaskSchedulerDeclarations.h"
    /**
     * @brief Decorador que permite detener la ejecución de una tarea al llamar
     *  a @c apagar(), pero no hacer nada al @c encender().
     */
    class PulsableDetenedor : public PulsableTarea {
        public:
            /**
             * @brief Construye un PulsableDetenedor, con el estado inicial
             *  y la tarea especificados.
             *
             * @param estadoInicial @c true para iniciar el programa con
             *  el objeto decorado encendido, @c false para el caso contrario.
             */
            PulsableDetenedor(bool estadoInicial, Task *tarea);

            /**
             * @brief No hace nada.
             */
            void encender(void) override;

            /**
             * @brief Detiene la ejecución de la tarea.
             */
            void apagar(void) override;

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

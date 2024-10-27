/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PULSABLE_INICIADOR
#define PULSABLE_INICIADOR

#include "CLASE_PulsableTarea.h"
#include "../../../Inclusiones/InclusionTaskSchedulerDeclarations.h"
    /**
     * @brief Decorador que permite reiniciar una tarea al llamar a
     *  @c encender(), pero no hacer nada al @c apagar().
     */
    class PulsableIniciador : public PulsableTarea {
        public:
            /**
             * @brief Construye un PulsableIniciador, con el estado inicial
             *  y la tarea especificados.
             *
             * @param estadoInicial @c true para iniciar el programa con
             *  el objeto decorado encendido, @c false para el caso contrario.
             */
            PulsableIniciador(bool estadoInicial, Task *tarea);

            /**
             * @brief Reinicia la tarea.
             */
            void encender(void) override;

            /**
             * @brief No hace nada.
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

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ADAPTADOR_PULSABLE_TAREA
#define ADAPTADOR_PULSABLE_TAREA

#include "CLASE_PulsableIniciador.h"
    /**
     * @brief Decorador que permite activar o desactivar una tarea como si
     *  @c Task fuera subclase de @c Pulsable.
     */
    class AdaptadorPulsableTarea : public PulsableIniciador {
        public:
            /**
             * @brief Construye un AdaptadorPulsableTarea, con el estado inicial
             *  y la tarea especificados.
             *
             * @param estadoInicial @c true para iniciar el programa con
             *  el objeto decorado encendido, @c false para el caso contrario.
             */
            AdaptadorPulsableTarea(bool estadoInicial, Task *tarea);

            /**
             * @brief Deshabilita la tarea adaptada.
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

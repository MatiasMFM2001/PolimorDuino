/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PULSABLE_CALLBACKS
#define PULSABLE_CALLBACKS

#include "CLASE_Pulsable.h"
#include "../../Medidores/Callbacks/INTERFAZ_CallbackResultado.h"
    /**
     * @brief Decorador que permite invocar instancias CallbackResultado<> al
     *  encenderlo y apagarlo.
     */
    class PulsableCallbacks : public Pulsable {
        private:
            /** @brief Puntero al callback a ejecutar en @c encender(). */
            CallbackResultado<> *callbackEncendido;
            
            /** @brief Puntero al callback a ejecutar en @c apagar(). */
            CallbackResultado<> *callbackApagado;

        public:
            /**
             * @brief Construye un PulsableCallbacks, con el estado inicial,
             *  callback de encendido y callback de apagado especificados.
             *
             * @param estadoInicial @c true para iniciar el programa con
             *  el objeto decorado encendido, @c false para el caso contrario.
             */
            PulsableCallbacks(bool estadoInicial, CallbackResultado<> *callbackEncendido, CallbackResultado<> *callbackApagado);

            /**
             * @brief Ejecuta al @c callbackEncendido.
             */
            void encender(void) override;

            /**
             * @brief Ejecuta al @c callbackApagado.
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

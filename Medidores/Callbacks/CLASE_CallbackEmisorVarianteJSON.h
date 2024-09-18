/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CALLBACK_EMISOR_VARIANTE_JSON
#define CALLBACK_EMISOR_VARIANTE_JSON

#include <Print.h>
#include <ArduinoJson.h>
#include "INTERFAZ_CallbackResultado.h"
    template <typename T_VARIANTE, size_t (*serializador)(const T_VARIANTE, Print&)>
    class CallbackEmisorVarianteJSON : public CallbackResultado<T_VARIANTE> {
        private:
            Print &salida;

        public:
            CallbackEmisorVarianteJSON(Print &salida)
                : salida(salida)
            {}

            void notificar(const T_VARIANTE &resultado) override {
                serializador(resultado, this -> salida);
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "CallbackEmisorVarianteJSON");
            }
    };
#endif
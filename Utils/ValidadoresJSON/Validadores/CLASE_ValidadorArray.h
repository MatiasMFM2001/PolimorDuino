/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_ARRAY
#define VALIDADOR_ARRAY

#include "CLASE_ValidadorCompuesto.h"
    template <size_t CAPACIDAD_CONDICIONES>
    class ValidadorArray : public ValidadorCompuesto<size_t, CAPACIDAD_CONDICIONES> {
        public:
            ValidadorArray(Array<CondicionValidador<size_t> *, CAPACIDAD_CONDICIONES> condiciones)
                : ValidadorCompuesto<size_t, CAPACIDAD_CONDICIONES>(condiciones)
            {}
            
            bool esValido(JsonVariant &variante) override {
                if (!variante.is<JsonArray>()) {
                    return false;
                }
                
                JsonArray array = variante.as<JsonArray>();
                
                for (size_t cont = 0; cont < array.size(); ++cont) {
                    JsonVariant valor = array[cont];

                    if (!(this -> esValido(valor, cont, "la posición"))) {
                        return false;
                    }
                }
                
                return true;
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "ValidadorArray") + SUPERCLASES_A_JSON(impresora, (ValidadorCompuesto<size_t, CAPACIDAD_CONDICIONES>));
            }

            using ValidadorCompuesto<size_t, CAPACIDAD_CONDICIONES>::esValido;
    };
#endif

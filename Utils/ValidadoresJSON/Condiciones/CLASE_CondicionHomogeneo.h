/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONDICION_HOMOGENEO
#define CONDICION_HOMOGENEO

#include "CLASE_CondicionValidador.h"
    template <typename T>
    class CondicionHomogeneo : public CondicionValidador<T> {
        public:
            CondicionHomogeneo(ValidadorJSON *hijo)
                : CondicionValidador<T>(hijo)
            {}
        
            bool puedeValidar(const T ingr) override {
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
                return OBJETO_A_JSON(impresora, "CondicionValidador") + SUPERCLASES_A_JSON(impresora, CondicionValidador<T>);
            }
    };
#endif

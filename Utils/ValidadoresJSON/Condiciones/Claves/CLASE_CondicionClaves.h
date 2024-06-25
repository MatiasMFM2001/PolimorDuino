/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONDICION_CLAVES
#define CONDICION_CLAVES

#include "../CLASE_CondicionValidador.h"
    class CondicionClaves : public CondicionValidador<const char *, JsonObject> {
        public:
            CondicionClaves(ValidadorJSON *hijo)
                : CondicionValidador<const char *, JsonObject>(hijo)
            {}
            
            virtual bool varianteContieneTodas(const JsonObject &ingr) = 0;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "CondicionClaves") + SUPERCLASES_A_JSON(impresora, (CondicionValidador<const char *, JsonObject>));
            }
    };
#endif

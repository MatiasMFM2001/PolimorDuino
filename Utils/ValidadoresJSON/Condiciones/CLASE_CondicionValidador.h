/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONDICION_VALIDADOR
#define CONDICION_VALIDADOR

#include "../CLASE_ValidadorJSON.h"
#include "../../../Logger/FuncionesJSON.h"
#include "../../../Inclusiones/InclusionLog4Arduino.h"
    template <typename T>
    class CondicionValidador : public CondicionResultado<JsonVariant> {
        private:
            ValidadorJSON *hijo;

        public:
            CondicionValidador(ValidadorJSON *hijo)
                : hijo(hijo)
            {}

            virtual bool puedeValidar(const T ingr) {
                LOG("ADVERTENCIA: No se debería estar ejecutando CondicionValidador::puedeValidar(const T)");
                return false;
            };

            bool esValido(JsonVariant &variante) override {
                return (this -> hijo -> esValido(variante));
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "CondicionValidador", hijo);
            }
    };
#endif

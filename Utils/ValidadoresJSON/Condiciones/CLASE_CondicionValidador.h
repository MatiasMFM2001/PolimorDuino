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
    template <typename T_IDENTIFICADOR, typename T_VARIANTE>
    class CondicionValidador : public CondicionJSON<> {
        private:
            ValidadorJSON *hijo;

        public:
            CondicionValidador(ValidadorJSON *hijo)
                : hijo(hijo)
            {}

            virtual bool puedeValidar([[maybe_unused]] const T_IDENTIFICADOR ingr) {
                LOG("ADVERTENCIA: No se debería estar ejecutando CondicionValidador::puedeValidar(const T_IDENTIFICADOR)");
                return false;
            };
            
            virtual bool varianteContieneTodas([[maybe_unused]] const T_VARIANTE &ingr, [[maybe_unused]] NodoPilaJSON &pilaClaves) {
                LOG("ADVERTENCIA: No se debería estar ejecutando CondicionValidador::varianteContieneTodas(const T_VARIANTE &, NodoPilaJSON &)");
                return false;
            };

            bool esValido(const JsonVariantConst &variante, NodoPilaJSON &pilaClaves) const override {
                return (this -> hijo -> esValido(variante, pilaClaves));
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

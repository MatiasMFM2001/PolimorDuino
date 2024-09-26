/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_PRIMITIVO
#define VALIDADOR_PRIMITIVO

#include "../CLASE_ValidadorJSON.h"
    template <typename T>
    class ValidadorPrimitivo : public ValidadorJSON {
        public:
            bool esValido(const JsonVariantConst &variante, NodoPilaJSON &pilaClaves) override {
                bool salida = variante.is<T>();
                
                if (!salida) {
                    pilaClaves.agregarFinalMensaje("El dato no es de tipo '");
                    pilaClaves.agregarFinalMensaje(conversores::tipoAString<T>());
                    pilaClaves.agregarFinalMensaje("'");
                }
                
                return salida;
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "ValidadorPrimitivo");
            }
    };
#endif

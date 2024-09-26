/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_OBJETO
#define VALIDADOR_OBJETO

#include "CLASE_ValidadorCompuesto.h"
#include "../NodosPila/CLASE_NodoConcretoPilaJSON.h"
    template <size_t CAPACIDAD_CONDICIONES>
    class ValidadorObjeto : public ValidadorCompuesto<const char *, JsonObjectConst, CAPACIDAD_CONDICIONES> {
        public:
            ValidadorObjeto(Array<CondicionValidador<const char *, JsonObjectConst> *, CAPACIDAD_CONDICIONES> condiciones, bool valorPredeterminado = false)
                : ValidadorCompuesto<const char *, JsonObjectConst, CAPACIDAD_CONDICIONES>(condiciones, valorPredeterminado)
            {}
            
            bool esValido(const JsonVariantConst &variante, NodoPilaJSON &pilaClaves) override {
                if (!variante.is<JsonObject>()) {
                    return false;
                }
                
                JsonObjectConst objeto = variante.as<JsonObjectConst>();
                
                if (!(this -> contieneTodas(objeto, pilaClaves))) {
                    CLOG("Retornando FALSE porque el objeto no contiene todas");
                    return false;
                }
                
                for (JsonPairConst selec: objeto) {
                    const char *clave = selec.key().c_str();
                    JsonVariantConst valor = selec.value();
                    NodoConcretoPilaJSON<const char *> nodo(clave, pilaClaves);

                    if (!(this -> esValido(valor, clave, "la clave", nodo))) {
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
                return OBJETO_A_JSON(impresora, "ValidadorObjeto") + SUPERCLASES_A_JSON(impresora, (ValidadorCompuesto<const char *, JsonObjectConst, CAPACIDAD_CONDICIONES>));
            }

            using ValidadorCompuesto<const char *, JsonObjectConst, CAPACIDAD_CONDICIONES>::esValido;
    };
#endif

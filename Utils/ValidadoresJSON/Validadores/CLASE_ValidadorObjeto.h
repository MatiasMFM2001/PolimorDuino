/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_OBJETO
#define VALIDADOR_OBJETO

#include "CLASE_ValidadorCompuesto.h"
    template <size_t CAPACIDAD_CONDICIONES>
    class ValidadorObjeto : public ValidadorCompuesto<const char *, JsonObject, CAPACIDAD_CONDICIONES> {
        public:
            ValidadorObjeto(Array<CondicionValidador<const char *, JsonObject> *, CAPACIDAD_CONDICIONES> condiciones)
                : ValidadorCompuesto<const char *, JsonObject, CAPACIDAD_CONDICIONES>(condiciones)
            {}
            
            bool esValido(JsonVariant &variante) override {
                if (!variante.is<JsonObject>()) {
                    return false;
                }
                
                CLOG("VARIANTE DE VALIDADOR:");
                serializeJsonPretty(variante, Serial);
                
                JsonObject objeto = variante.as<JsonObject>();
                
                if (!(this -> contieneTodas(objeto))) {
                    CLOG("Retornando FALSE porque el objeto no contiene todas");
                    return false;
                }
                
                for (JsonPair selec: objeto) {
                    JsonVariant valor = selec.value();

                    CLOG("BAJO LA CLAVE", selec.key().c_str(), "SE ENCUENTRA EL VALOR:");
                    serializeJsonPretty(valor, Serial);

                    if (!(this -> esValido(valor, selec.key().c_str(), "la clave"))) {
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
                return OBJETO_A_JSON(impresora, "ValidadorObjeto") + SUPERCLASES_A_JSON(impresora, (ValidadorCompuesto<const char *, JsonObject, CAPACIDAD_CONDICIONES>));
            }

            using ValidadorCompuesto<const char *, JsonObject, CAPACIDAD_CONDICIONES>::esValido;
    };
#endif

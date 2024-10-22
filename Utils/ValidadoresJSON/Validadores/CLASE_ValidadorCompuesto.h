/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_COMPUESTO
#define VALIDADOR_COMPUESTO

#include "../CLASE_ValidadorJSON.h"
#include <Array.h>
#include "../Condiciones/CLASE_CondicionValidador.h"
#include "../../../Logger/FuncionesLoggers.h"
#include "../../NAMESPACE_Conversores.h"
    template <typename T_CONDICION, typename T_VARIANTE_CONDICION, size_t CAPACIDAD_CONDICIONES>
    class ValidadorCompuesto : public ValidadorJSON {
        private:
            Array<CondicionValidador<T_CONDICION, T_VARIANTE_CONDICION> *, CAPACIDAD_CONDICIONES> condiciones;
            bool valorPredeterminado;
        
        protected:
            bool contieneTodas(const T_VARIANTE_CONDICION &variante, NodoPilaJSON &pilaClaves) const {
                FLOGS("Ejecutando ValidadorCompuesto::contieneTodas()");

                for (CondicionValidador<T_CONDICION, T_VARIANTE_CONDICION> *condicion: this -> condiciones) {
                    if (!condicion) {
                        FLOGS("ValidadorCompuesto::contieneTodas() - ERROR: Condicion nula. Skippeando...");
                        continue;
                    }
                    
                    if (!(condicion -> varianteContieneTodas(variante, pilaClaves))) {
                        CLOG(F("Para esta condicion la variante no contiene todas: "), *condicion);

                        AdaptadorStringImpresora salida = pilaClaves.getAdaptadorMensaje();

                        salida.print(F("La variante compuesta de tipo '"));
                        salida.print(conversores::tipoAString<T_VARIANTE_CONDICION>());
                        salida.print(F("' no contiene todas las claves/índices requeridos"));

                        pilaClaves.setDatoErroneo(variante);
                        pilaClaves.guardarNodosPila();

                        return false;
                    }
                }
                
                return true;
            }
        
            bool esValido(const JsonVariantConst &variante, const T_CONDICION ingr, [[maybe_unused]] const char *nombreIngr, NodoPilaJSON &pilaClaves) const {
                for (CondicionValidador<T_CONDICION, T_VARIANTE_CONDICION> *condicion: this -> condiciones) {
                    if (!(condicion -> puedeValidar(ingr))) {
                        continue;
                    }
                    
                    return (condicion -> esValido(variante, pilaClaves));
                }
                
                CLOG(F("ADVERTENCIA: Ninguna condición de este ValidadorCompuesto cubre"), nombreIngr, ingr, F(". Retornando "), this -> valorPredeterminado);
                return (this -> valorPredeterminado);
            }
        
        public:
            ValidadorCompuesto(Array<CondicionValidador<T_CONDICION, T_VARIANTE_CONDICION> *, CAPACIDAD_CONDICIONES> condiciones, bool valorPredeterminado)
                : condiciones(condiciones), valorPredeterminado(valorPredeterminado)
            {}

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "ValidadorCompuesto", condiciones);
            }

            using ValidadorJSON::esValido;
    };
#endif

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef LISTA_CLAVES
#define LISTA_CLAVES

#include "CLASE_CondicionClaves.h"
#include <Array.h>
#include "../../../FuncionesGlobales.h"
    template <size_t CAPACIDAD_LISTA>
    class ListaClaves : public CondicionClaves {
        private:
            Array<const char *, CAPACIDAD_LISTA> lista;
        
            bool objetoContieneClave(const JsonObjectConst &ingr, const char *clave) {
                for (JsonPairConst selec: ingr) {
                    CLOG("COMPARANDO CLAVE", selec.key().c_str(), "Y", clave);
                    if (cadenasIguales(selec.key().c_str(), clave)) {
                        CLOG("Son iguales");
                        return true;
                    }
                }
                
                return false;
            }
            
        public:
            ListaClaves(ValidadorJSON *hijo, Array<const char *, CAPACIDAD_LISTA> lista)
                : CondicionClaves(hijo)
                , lista(lista)
            {}
            
            bool puedeValidar(const char *ingr) {
                return contiene<const char *, CAPACIDAD_LISTA>(this -> lista, ingr, &cadenasIguales);
            }
            
            bool varianteContieneTodas(const JsonObjectConst &ingr, NodoPilaJSON &pilaClaves) override {
                for (const char *selec: this -> lista) {
                    if (!(this -> objetoContieneClave(ingr, selec))) {
                        CLOG("El objeto no contiene esta clave:", selec);
                        
                        pilaClaves.agregarFinalMensaje("El objeto no contiene la clave '");
                        pilaClaves.agregarFinalMensaje(selec);
                        pilaClaves.agregarFinalMensaje("'");
                        
                        pilaClaves.setDatoErroneo(ingr);
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
                return OBJETO_A_JSON(impresora, "ListaClaves", lista) + SUPERCLASES_A_JSON(impresora, CondicionClaves);
            }
    };
#endif

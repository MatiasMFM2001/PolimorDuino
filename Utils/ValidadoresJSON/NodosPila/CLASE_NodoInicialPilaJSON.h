/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef NODO_INICIAL_PILA_JSON
#define NODO_INICIAL_PILA_JSON

#include "INTERFAZ_NodoPilaJSON.h"
#include "../../EstructurasDatos/Cadenas/CLASE_StringEstatica.h"
    template <size_t CAPACIDAD_PILA_JSON, size_t CAPACIDAD_MENSAJE>
    class NodoInicialPilaJSON : public NodoPilaJSON {
        private:
            StaticJsonDocument<CAPACIDAD_PILA_JSON> pilaClaves;
            JsonVariantConst datoErroneo;
            StringEstatica<CAPACIDAD_MENSAJE> mensaje;
        
        public:
            NodoInicialPilaJSON()
                : pilaClaves(StaticJsonDocument<CAPACIDAD_PILA_JSON>()), datoErroneo(JsonVariant()), mensaje(StringEstatica<CAPACIDAD_MENSAJE>())
            {}

            JsonArray guardarNodosPila(void) override {
                FLOGS("Se llamó a NodoInicialPilaJSON::guardarNodosPila()");
                return (this -> pilaClaves.template to<JsonArray>());
            }
            
            void setDatoErroneo(const JsonVariantConst ingr) override {
                FLOGS("Se llamó a NodoInicialPilaJSON::setDatoErroneo()");
                this -> datoErroneo = ingr;
            }
            
            bool agregarFinalMensaje(const char *ingr) override {
                CLOG(F("Se llamó a NodoInicialPilaJSON::guardarNodosPila("), ingr, ')');
                return (this -> mensaje.agregarFinal(ingr));
            }
            
            AdaptadorStringImpresora getAdaptadorMensaje(void) override {
                return AdaptadorStringImpresora(&(this -> mensaje));
            }
            
            size_t imprimirResultadoErroneo(Print &impresora, const char *nombreVariable) {
                FLOGS("Se llamó a NodoInicialPilaJSON::imprimirResultadoErroneo()");
                
                if ((this -> pilaClaves.size()) == 0) {
                    impresora.println(F("ADVERTENCIA: Se llamó a NodoInicialPilaJSON::imprimirResultadoErroneo() pero la pila está vacía"));
                    return 0;
                }
                
                size_t salida = impresora.println(this -> mensaje.getContenidoConstante());
                
                salida += impresora.print(F("- RUTA: "));
                salida += impresora.print(nombreVariable);
                
                for (JsonVariantConst selec: (this -> pilaClaves.template as<JsonArrayConst>())) {
                    salida += impresora.print('[');
                    salida += serializeJson(selec, impresora);
                    salida += impresora.print(']');
                }
                
                salida += impresora.print(F(" = "));
                salida += serializeJson(this -> datoErroneo, impresora);
                salida += impresora.println();
                
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
                return OBJETO_SIN_SUPER_A_JSON(impresora, "NodoInicialPilaJSON");
            }
    };
#endif

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef NODO_INICIAL_PILA_JSON
#define NODO_INICIAL_PILA_JSON

#include "INTERFAZ_NodoPilaJSON.h"
    template <size_t CAPACIDAD_PILA_JSON, size_t CAPACIDAD_MENSAJE>
    class NodoInicialPilaJSON : public NodoPilaJSON {
        private:
            StaticJsonDocument<CAPACIDAD_PILA_JSON> pilaClaves;
            JsonVariant datoErroneo;
            StringEstatica<CAPACIDAD_MENSAJE> mensaje;
        
        public:
            NodoInicialPilaJSON()
                : pilaClaves(StaticJsonDocument<CAPACIDAD_PILA_JSON>()), datoErroneo(JsonVariant()), mensaje(StringEstatica<CAPACIDAD_MENSAJE>())
            {}

            JsonArray copiarLista(void) override {
                return (this -> pilaClaves.template to<JsonArray>());
            }
            
            bool agregarFinalMensaje(const char *ingr) override {
                return (this -> mensaje.agregarFinal(ingr));
            }
            
            void setDatoErroneo(JsonVariant ingr) override {
                this -> datoErroneo = ingr;
            }
            
            size_t imprimirResultadoErroneo(Print &impresora, const char *nombreVariable) {
                if ((this -> pilaClaves.size()) == 0) {
                    return 0;
                }
                
                size_t salida = impresora.println(this -> mensaje.getContenidoConstante());
                
                salida += impresora.print("- RUTA: ");
                salida += impresora.print(nombreVariable);
                
                for (JsonVariant selec: this -> pilaClaves) {
                    salida += impresora.print('[');
                    salida += serializeJson(selec, impresora);
                    salida += impresora.print(']');
                }
                
                salida += impresora.print(" = ");
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

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef NODO_CONCRETO_PILA_JSON
#define NODO_CONCRETO_PILA_JSON

#include "INTERFAZ_NodoPilaJSON.h"
    template <typename T_DATO>
    class NodoConcretoPilaJSON : public NodoPilaJSON {
        private:
            const T_DATO dato;
            NodoPilaJSON &anterior;
        
        public:
            NodoConcretoPilaJSON(const T_DATO dato, NodoPilaJSON &anterior)
                : dato(dato), anterior(anterior)
            {}

            JsonArray copiarLista(void) override {
                JsonArray salida = (this -> anterior.copiarLista());
                salida.add(this -> dato);
                
                return salida;
            }
            
            bool agregarFinalMensaje(const char *ingr) override {
                return (this -> anterior.agregarFinalMensaje(ingr));
            }
            
            void setDatoErroneo(JsonVariant ingr) override {
                this -> anterior.setDatoErroneo(ingr);
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "NodoConcretoPilaJSON", dato, anterior);
            }
    };
#endif

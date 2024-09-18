/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SELECTOR_CALLBACK
#define SELECTOR_CALLBACK   

#include <Array.h>
    template <size_t CAPACIDAD_HIJOS, typename... T>
    class SelectorCallback: public CallbackResultado<T...> {
        private:
            Array<CallbackResultado<T...> *, CAPACIDAD_HIJOS> hijos;
            size_t posActual;
        
        public:
            SelectorCallback(Array<CallbackResultado<T...> *, CAPACIDAD_HIJOS> hijos)
                : hijos(hijos), posActual(0)
            {}
            
            void notificar(const T&... resultado) override {
                CallbackResultado<T...> *selec = this -> hijos[this -> posActual];
                
                if (!selec) {
                    return;
                }
                
                selec -> notificar(resultado...);
            }
            
            void incrementarCircular(void) {
                this -> posActual++;
                
                if ((this -> posActual) >= (this -> hijos.size())) {
                    this -> posActual = 0;
                }
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "SelectorCallback", hijos, posActual);
            }
    };
#endif

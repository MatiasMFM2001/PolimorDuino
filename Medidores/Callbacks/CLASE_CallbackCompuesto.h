/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CALLBACK_COMPUESTO
#define CALLBACK_COMPUESTO   

#include <Array.h>
    template <size_t CAPACIDAD_HIJOS, typename... T>
    class CallbackCompuesto: public CallbackResultado<T...> {
        private:
            Array<CallbackResultado<T...> *, CAPACIDAD_HIJOS> hijos;
        
        public:
            CallbackCompuesto(Array<CallbackResultado<T...> *, CAPACIDAD_HIJOS> hijos)
                : hijos(hijos)
            {}
            
            void notificar(const T&... resultado) override {
                for (CallbackResultado<T...> *selec: this -> hijos) {
                    if (!selec) {
                        continue;
                    }
                    
                    selec -> notificar(resultado...);
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
                return OBJETO_SIN_SUPER_A_JSON(impresora, "CallbackCompuesto", hijos);
            }
    };
#endif

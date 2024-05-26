/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CALLBACK_INICIADOR
#define CALLBACK_INICIADOR

#include <Printable.h>
    template <typename... T>
    class CallbackIniciador: public CallbackResultado<T...> {
        private:
            Task *tarea;
        
        public:
            CallbackIniciador(Task *tarea)
                : tarea(tarea)
            {}
            
            void notificar(T&... resultado) override {
                this -> tarea -> enableIfNot();
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "CallbackIniciador");
            }
    };
#endif
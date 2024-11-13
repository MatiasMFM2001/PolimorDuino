/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CALLBACK_LLAMADOR_METODO
#define CALLBACK_LLAMADOR_METODO

#include "INTERFAZ_CallbackResultado.h"
    template <typename T_OBJETO, void(T_OBJETO::*METODO_OBJETO)(void), typename... T_ARGUMENTOS>
    class CallbackLlamadorMetodo : public CallbackResultado<T_ARGUMENTOS...> {
        private:
            T_OBJETO *objeto;
            
        public:
            CallbackLlamadorMetodo(T_OBJETO *objeto)
                : objeto(objeto)
            {}
        
            void notificar(const T_ARGUMENTOS&... resultado) override {
                (this -> objeto ->* METODO_OBJETO)();
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "CallbackLlamadorMetodo");
            }
    };
#endif

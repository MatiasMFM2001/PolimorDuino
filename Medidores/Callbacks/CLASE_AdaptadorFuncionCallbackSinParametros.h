/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ADAPTADOR_FUNCION_CALLBACK_SIN_PARAMETROS
#define ADAPTADOR_FUNCION_CALLBACK_SIN_PARAMETROS

#include "INTERFAZ_CallbackResultado.h"
#include "../../Logger/FuncionesJSON.h"
    template <typename... T>
    class AdaptadorFuncionCallbackSinParametros: public CallbackResultado<T...> {
        private:
            void (*funcion)(void);
        
        public:
            AdaptadorFuncionCallback(void (*funcion)(void))
                : funcion(funcion)
            {}
            
            void notificar(T&... resultado) override {
                this -> funcion();
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "AdaptadorFuncionCallbackSinParametros");
            }
    };
#endif

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ADAPTADOR_FUNCION_CONDICION
#define ADAPTADOR_FUNCION_CONDICION

#include "INTERFAZ_CondicionResultado.h"
    template <typename... T>
    class AdaptadorFuncionCondicion : public CondicionResultado<T...> {
        private:
           bool (*condicion)(T...);
        
        public:
            AdaptadorFuncionCondicion(bool (*condicion)(T...))
                : condicion(condicion)
            {}
        
            bool esValido(T&... resultado) override {
                return (this -> condicion(resultado...));
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "AdaptadorFuncionCondicion");
            }
    };
#endif

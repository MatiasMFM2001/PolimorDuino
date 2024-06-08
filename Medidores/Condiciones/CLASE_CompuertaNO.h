/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef COMPUERTA_NO
#define COMPUERTA_NO

#include "INTERFAZ_CondicionResultado.h"
    template <typename... T>
    class CompuertaNO : public CondicionResultado<T...> {
        private:
            CondicionResultado<T...> *condicion;
        
        public:
            CompuertaNO(CondicionResultado<T...> *condicion)
                : condicion(condicion)
            {}
        
            bool esValido(T&... resultado) override {
                return !(this -> condicion -> esValido(resultado...));
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "CompuertaNO", condicion);
            }
    };
#endif

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ADAPTADOR_FUNCION_COMPARADOR_IGUALDAD
#define ADAPTADOR_FUNCION_COMPARADOR_IGUALDAD

#include "INTERFAZ_ComparadorIgualdad.h"
    template <typename T>
    class AdaptadorFuncionComparadorIgualdad : public ComparadorIgualdad<T> {
        private:
            bool (*funcion)(const T &, const T &);
        
        public:
            AdaptadorFuncionComparadorIgualdad(bool (*funcion)(const T &, const T &))
                : funcion(funcion)
            {}
        
            bool sonIguales(const T &valor1, const T &valor2) const override {
                return (this -> funcion(valor1, valor2));
            }
    };
#endif

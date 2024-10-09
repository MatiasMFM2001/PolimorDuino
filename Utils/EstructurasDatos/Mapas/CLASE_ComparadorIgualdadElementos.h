/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef COMPARADOR_IGUALDAD_ELEMENTOS
#define COMPARADOR_IGUALDAD_ELEMENTOS

#include "../Conjuntos/INTERFAZ_ComparadorIgualdad.h"
#include "CLASE_ElementoMapa.h"
    template <typename T_CLAVES, typename T_VALORES>
    class ComparadorIgualdadElementos : public ComparadorIgualdad<ElementoMapa<T_CLAVES, T_VALORES>> {
        private:
            ComparadorIgualdad<T_CLAVES> *comparadorClaves;
        
        public:
            ComparadorIgualdadElementos(ComparadorIgualdad<T_CLAVES> *comparadorClaves)
                : comparadorClaves(comparadorClaves)
            {}
        
            bool sonIguales(const ElementoMapa<T_CLAVES, T_VALORES> &elem1, const ElementoMapa<T_CLAVES, T_VALORES> &elem2) override {
                return (this -> comparadorClaves -> sonIguales(elem1.getClave(), elem2.getClave()));
            }
    };
#endif

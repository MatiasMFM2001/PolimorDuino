/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENTRADA
#define ENTRADA

#include "../CLASE_EntradaSalida.h"
    template <typename T, byte N_NUM_BITS>
    class Entrada : public EntradaSalida<T, N_NUM_BITS> {
        protected:
            virtual T leerBajoNivel(void) = 0;
            
        public:
            Entrada(bool invertir)
                : EntradaSalida<T, N_NUM_BITS>(invertir)
            {}
            
            T leer() {
                T valor = this -> leerBajoNivel();
                T maxValor = this -> getMaxValorRepresentable();
                
                if (valor > maxValor) {
                    LOG("Entrada::leer() - Se leyo un valor %d mayor al maximo de %d", valor, maxValor);
                    return this -> invertirValor(maxValor);
                }
                
                return this -> invertirValor(valor);
            }
    };
#endif

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SALIDA
#define SALIDA

#include "../CLASE_EntradaSalida.h"
#include "../../Inclusiones/InclusionLog4Arduino.h"
    template <typename T, byte N_NUM_BITS>
    class Salida : public EntradaSalida<T, N_NUM_BITS> {
        protected:
            virtual void escribirBajoNivel(T valor) = 0;
            
        public:
            Salida(bool invertir)
                : EntradaSalida<T, N_NUM_BITS>(invertir)
            {}
            
            void escribir(T valor) {
                T maxValor = this -> getMaxValorRepresentable();
                
                if (valor > maxValor) {
                    LOG("Entrada::escribir() - Se escribio un valor %d mayor al maximo de %d", valor, maxValor);
                    this -> escribirBajoNivel(this -> invertirValor(maxValor));
                    return;
                }
                
                this -> escribirBajoNivel(this -> invertirValor(valor));
            }
    };
#endif

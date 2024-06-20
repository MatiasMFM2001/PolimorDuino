/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SALIDA_CONTINUA
#define SALIDA_CONTINUA

#include "CLASE_Salida.h"
    template <typename T, byte N_NUM_BITS>
    class SalidaContinua : public Salida<T, N_NUM_BITS> {
        public:
            SalidaContinua(bool invertir)
                : Salida<T, N_NUM_BITS>(invertir)
            {}
            
            virtual void setResolucion(byte numBits) override {
            }
    };
#endif

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENTRADA_ANALOGICA
#define ENTRADA_ANALOGICA

#include "CLASE_Entrada.h"
    template <typename T, byte N_NUM_BITS>
    class EntradaAnalogica : public Entrada<T, N_NUM_BITS> {
        public:
            EntradaAnalogica(bool invertir)
                : Entrada<T, N_NUM_BITS>(invertir)
            {}
    };
#endif

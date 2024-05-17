/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SALIDA_ANALOGICA
#define SALIDA_ANALOGICA

#include "CLASE_SalidaContinua.h"
    template <typename T, byte N_NUM_BITS>
    class SalidaAnalogica : public SalidaContinua<T, N_NUM_BITS> {
        public:
            SalidaAnalogica(bool invertir)
                : SalidaContinua<T, N_NUM_BITS>(invertir)
            {}
    };
#endif

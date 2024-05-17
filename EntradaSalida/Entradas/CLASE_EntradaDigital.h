/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENTRADA_DIGITAL
#define ENTRADA_DIGITAL

#include "CLASE_Entrada.h"
#include "../TIPOS_EnterosAnalogicos.h"
    class EntradaDigital : public Entrada<BOOL_1_BIT> {
        public:
            EntradaDigital(bool invertir);
    };
#endif

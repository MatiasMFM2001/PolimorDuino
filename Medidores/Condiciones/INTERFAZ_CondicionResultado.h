/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONDICION_RESULTADO
#define CONDICION_RESULTADO

#include "INTERFAZ_CondicionResultadoMutable.h"
    template <typename... T>
    class CondicionResultado : public CondicionResultadoMutable<const T...> {
    };
#endif

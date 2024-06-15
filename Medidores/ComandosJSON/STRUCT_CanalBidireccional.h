/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CANAL_BIDIRECCIONAL
#define CANAL_BIDIRECCIONAL

#include <Stream.h>
    template <typename T_ENTRADA, typename T_SALIDA>
    struct CanalBidireccional {
        T_ENTRADA &entrada;
        T_SALIDA &salida;
    };
#endif

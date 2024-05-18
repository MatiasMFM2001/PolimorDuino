/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FUNCIONES_LOGGERS
#define FUNCIONES_LOGGERS

#include <Printable.h>
    template <typename T>
    void imprimir(T &valor) {
        log4arduino_print_head();
        _log4arduino_target -> println(valor);
    }
#endif

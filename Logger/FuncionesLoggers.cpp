/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "FuncionesLoggers.h"
#include "../Inclusiones/InclusionLog4Arduino.h"

void imprimir(unsigned short &valor) {
    LOG("%d", valor);
} 

void imprimir(arduino::Printable &valor) {
    log4arduino_print_head();
    _log4arduino_target -> println(valor);
}

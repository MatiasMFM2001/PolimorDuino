/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FUNCIONES_LOGGERS
#define FUNCIONES_LOGGERS

#include <Printable.h>
#include "../Inclusiones/InclusionLog4Arduino.h"
#include "MACRO_ForEachAcumulando.h"
    #define IMPRIMIR_DATO(impresora, valor) (impresora).print(valor); (impresora).print(' ');
    #define CLOG_REFERENCIA_IMPRESORA(impresora, ...) FOR_EACH_ACUMULANDO(IMPRIMIR_DATO, (impresora), __VA_ARGS__); (impresora).print('\n');
    #define CLOG_PUNTERO_IMPRESORA(impresora, ...) if (impresora) {CLOG_REFERENCIA_IMPRESORA(*impresora, __VA_ARGS__)}
    
    #ifdef ENABLE_LOG4ARDUINO
        #define CLOG(...) log4arduino_print_head(); CLOG_PUNTERO_IMPRESORA(_log4arduino_target, __VA_ARGS__);
    #else
        #define CLOG(...)
    #endif
    
    template <typename T>
    void imprimir(T &valor) {
        CLOG(valor);
    }
#endif

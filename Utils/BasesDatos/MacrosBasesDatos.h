/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "../../Medidores/ComandosJSON/CallbacksComandos/FuncionesComandos.h"

#define OBTENER_VALOR_BD_VARIABLE_EXTERNA(baseDatos, salida, clave, valorPredeterminado, nombreValor, variableASobreescribir, ...) \
    if (baseDatos.getValorSetteando(clave, valorPredeterminado, variableASobreescribir, salida)) { \
        __VA_ARGS__; \
    } else { \
        CLOG(F("ERROR: No se pudo obtener el "), nombreValor, F(" '"), clave, '\''); \
    }

#define OBTENER_VALOR_BD_VARIABLE_INTERNA(baseDatos, salida, clave, valorPredeterminado, nombreValor, tipoDatoVariable, variableASobreescribir, ...) \
    do { \
        tipoDatoVariable variableASobreescribir; \
        OBTENER_VALOR_BD_VARIABLE_EXTERNA(baseDatos, salida, clave, valorPredeterminado, nombreValor, variableASobreescribir, __VA_ARGS__); \
    } \
    while(false);

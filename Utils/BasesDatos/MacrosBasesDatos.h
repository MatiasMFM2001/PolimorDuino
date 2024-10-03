/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "../../Medidores/ComandosJSON/CallbacksComandos/FuncionesComandos.h"

#define OBTENER_VALOR_BD_VARIABLE_EXTERNA(baseDatos, salida, clave, valorPredeterminado, nombreValor, variableASobreescribir, expresionCompletaVariable) \
    if (baseDatos.getValorSetteando(clave, valorPredeterminado, variableASobreescribir, salida)) { \
        expresionCompletaVariable; \
    } else { \
        CLOG("ERROR: No se pudo obtener el ", nombreValor, " '", clave, '\''); \
    }

#define OBTENER_VALOR_BD_VARIABLE_INTERNA(baseDatos, salida, clave, valorPredeterminado, nombreValor, tipoDatoVariable, variableASobreescribir, expresionCompletaVariable) \
    do { \
        tipoDatoVariable variableASobreescribir; \
        OBTENER_VALOR_BD_VARIABLE_EXTERNA(baseDatos, salida, clave, valorPredeterminado, nombreValor, variableASobreescribir, expresionCompletaVariable); \
    } \
    while(false);

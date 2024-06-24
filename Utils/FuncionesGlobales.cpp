/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//#include "DeclaracionVariablesGlobales.h"
#include "FuncionesGlobales.h"
#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"

long multiplicarNumIteraciones(long numTerminos, unsigned long multiplicador) {
    if (numTerminos == TASK_FOREVER) {
        return TASK_FOREVER;
    }
    
    return (numTerminos * multiplicador);
}

bool cadenasIguales(const char* const &valor1, const char* const &valor2) {
    return (strcmp(valor1, valor2) == 0);
}

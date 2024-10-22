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

bool cadenasIguales(const char *valor1, const __FlashStringHelper* const &valor2) {
    if (!valor1) {
        return !valor2;
    }
    
    if (!valor2) {
        return false;
    }
    
    PGM_P p = reinterpret_cast<PGM_P>(valor2);
    char selec = pgm_read_byte(p);
    
    while ((selec != '\0') && (*valor1 != '\0') && (selec == *valor1)) {
        selec = pgm_read_byte(++p);
        ++valor1;
    }
    
    return (selec == *valor1);
}

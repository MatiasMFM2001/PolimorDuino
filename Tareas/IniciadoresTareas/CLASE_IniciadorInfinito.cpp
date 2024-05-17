/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_IniciadorInfinito.h"
#include "../../Logger/FuncionesJSON.h"

IniciadorInfinito::IniciadorInfinito(unsigned long msEntreIniciaciones, Scheduler* planif, Task *tarea)
    : IniciadorTareas(msEntreIniciaciones, planif, tarea)
{}

bool IniciadorInfinito::deboFinalizar(void) {
    return false;
}

size_t IniciadorInfinito::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "IniciadorInfinito");
}

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_PulsableIniciador.h"
#include "../../../Logger/FuncionesJSON.h"

PulsableIniciador::PulsableIniciador(bool estadoInicial, Task *tarea)
    : PulsableTarea(estadoInicial, tarea)
{}

void PulsableIniciador::encender(void) {
    this -> tarea -> restart();
}

void PulsableIniciador::apagar(void) {
} 

size_t PulsableIniciador::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "PulsableIniciador") + SUPERCLASES_A_JSON(impresora, PulsableTarea);
}

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_PulsableDetenedor.h"
#include "../../../Logger/FuncionesJSON.h"

PulsableDetenedor::PulsableDetenedor(bool estadoInicial, Task *tarea)
    : PulsableTarea(estadoInicial, tarea)
{}

void PulsableDetenedor::encender(void) {
}

void PulsableDetenedor::apagar(void) {
    this -> tarea -> disable();
} 

size_t PulsableDetenedor::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "PulsableDetenedor") + SUPERCLASES_A_JSON(impresora, PulsableTarea);
}

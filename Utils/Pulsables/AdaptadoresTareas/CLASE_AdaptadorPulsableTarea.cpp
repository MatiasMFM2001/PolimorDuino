/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_AdaptadorPulsableTarea.h"
#include "../../../Logger/FuncionesJSON.h"

AdaptadorPulsableTarea::AdaptadorPulsableTarea(bool estadoInicial, Task *tarea)
    : PulsableIniciador(estadoInicial, tarea)
{}

void AdaptadorPulsableTarea::apagar(void) {
    this -> tarea -> disable();
} 

size_t AdaptadorPulsableTarea::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "AdaptadorPulsableTarea") + SUPERCLASES_A_JSON(impresora, PulsableIniciador);
}

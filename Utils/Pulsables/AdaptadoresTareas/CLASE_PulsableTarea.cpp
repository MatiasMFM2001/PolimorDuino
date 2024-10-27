/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_PulsableTarea.h"
#include "../../../Logger/FuncionesJSON.h"

PulsableTarea::PulsableTarea(bool estadoInicial, Task *tarea)
    : Pulsable(estadoInicial, false)
    , tarea(tarea)
{
    this -> setEstado(estadoInicial);
}

size_t PulsableTarea::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "PulsableTarea");
}

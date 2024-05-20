/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_InversorPulsable.h"
#include "../Logger/FuncionesJSON.h"

InversorPulsable::InversorPulsable(bool estadoInicial, Pulsable *decorado)
    : Pulsable(!estadoInicial, false)
    , decorado(decorado)
{
    this -> setEstado(!estadoInicial);
}

void InversorPulsable::encender(void) {
    this -> decorado -> apagar();
}

void InversorPulsable::apagar(void) {
    this -> decorado -> encender();
} 

size_t InversorPulsable::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "InversorPulsable", decorado);
}

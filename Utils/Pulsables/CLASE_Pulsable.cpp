/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_Pulsable.h"
#include "../Logger/FuncionesJSON.h"

Pulsable::Pulsable(bool estadoInicial, bool settearEstado) {
    if (settearEstado) {
        this -> setEstado(estadoInicial);
    }
}

void Pulsable::encender(void) {
    this -> setEstado(true);
}

void Pulsable::apagar(void) {
    this -> setEstado(false);
}

void Pulsable::setEstadoActual(bool valor) {
    this -> estadoActual = valor;
}

void Pulsable::setEstado(bool valor) {
    this -> setEstadoActual(valor);
    
    if (valor) {
        this -> encender();
    }
    else {
        this -> apagar();
    }
}

bool Pulsable::getEstado(void) {
    return (this -> estadoActual);
}

void Pulsable::invertirEstado(void) {
    this -> setEstado(!(this -> estadoActual));
}

size_t Pulsable::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "Pulsable", estadoActual);
}

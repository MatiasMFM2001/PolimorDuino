/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_SalidaDigital.h"

SalidaDigital::SalidaDigital(bool invertir, bool estadoInicial, bool settearEstado)
    : Salida<BOOL_1_BIT>(invertir)
    , Pulsable(estadoInicial, settearEstado)
{}

void SalidaDigital::setEstado(bool valor) {
    this -> escribir(valor);
}

size_t SalidaDigital::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "SalidaDigital") + SUPERCLASES_A_JSON(impresora, (Salida<BOOL_1_BIT>), Pulsable);
}

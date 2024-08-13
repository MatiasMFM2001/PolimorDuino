/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_PulsableCallbacks.h"
#include "../../Logger/FuncionesJSON.h"

PulsableCallbacks::PulsableCallbacks(bool estadoInicial, CallbackResultado<> *callbackEncendido, CallbackResultado<> *callbackApagado)
    : Pulsable(estadoInicial, false)
    , callbackEncendido(callbackEncendido), callbackApagado(callbackApagado)
{
    //this -> setEstado(estadoInicial);
}

void PulsableCallbacks::encender(void) {
    this -> setEstadoActual(true);
    this -> callbackEncendido -> notificar();
}

void PulsableCallbacks::apagar(void) {
    this -> setEstadoActual(false);
    this -> callbackApagado -> notificar();
} 

size_t PulsableCallbacks::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "PulsableCallbacks", callbackEncendido, callbackApagado);
}

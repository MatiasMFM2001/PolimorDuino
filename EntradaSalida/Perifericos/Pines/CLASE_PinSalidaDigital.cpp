/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_PinSalidaDigital.h"
#include "../../../Inclusiones/InclusionLog4Arduino.h"

PinSalidaDigital::PinSalidaDigital(pin_size_t numPin, bool invertir, bool estadoInicial)
    : Pin<OUTPUT>(numPin, NUM_DIGITAL_PINS)
    , SalidaDigital(invertir, estadoInicial, false)
{
    this -> setEstadoActual(estadoInicial);
}

void PinSalidaDigital::escribirBajoNivel(bool valor) {
    LOG("INICIO PinSalidaDigital::escribirBajoNivel(%d, %d)", this -> numPin, valor);
        if (this -> pinValido) {
            LOG("PinSalidaDigital::escribirBajoNivel(%d, %d) - Ejecutando por pin válido", this -> numPin, valor);
            digitalWrite(this -> numPin, valor ? HIGH : LOW);
        }
    LOG("FIN PinSalidaDigital::escribirBajoNivel(%d, %d)", this -> numPin, valor);
}

size_t PinSalidaDigital::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "PinSalidaDigital") + SUPERCLASES_A_JSON(impresora, Pin, SalidaDigital);
}

void PinSalidaDigital::inicializar(void) {
    Pin::inicializar();

    this -> setEstado(this -> getEstado());
}

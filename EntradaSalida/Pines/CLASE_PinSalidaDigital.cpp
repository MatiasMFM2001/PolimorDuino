#include "CLASE_PinSalidaDigital.h"
#include "InclusionLog4Arduino.h"

PinSalidaDigital::PinSalidaDigital(byte numPin, bool invertir, bool estadoInicial)
    : Pin(numPin, OUTPUT, NUM_DIGITAL_PINS)
    , SalidaDigital(invertir, estadoInicial)
{}

void PinSalidaDigital::escribirBajoNivel(bool valor) {
    LOG("INICIO PinSalidaDigital::escribirBajoNivel(%d, %d)", this -> numPin, valor);
        if (this -> pinValido) {
            LOG("PinSalidaDigital::escribirBajoNivel(%d, %d) - Ejecutando por pin válido", this -> numPin, valor);
            digitalWrite(this -> numPin, valor ? HIGH : LOW);
        }
    LOG("FIN PinSalidaDigital::escribirBajoNivel(%d, %d)", this -> numPin, valor);
}

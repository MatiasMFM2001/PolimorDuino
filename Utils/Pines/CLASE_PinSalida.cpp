#include "CLASE_PinSalida.h"
#include "InclusionLog4Arduino.h"

PinSalida::PinSalida(byte numPin, bool invertir, bool estadoInicial)
    : Pin(numPin, invertir, OUTPUT)
    , Pulsable(estadoInicial)
{}

void PinSalida::setEstado(bool valor) {
    LOG("INICIO PinSalida::setEstado(%d, %d)", this -> numPin, valor);
        if (this -> pinValido) {
            LOG("PinSalida::setEstado(%d, %d) - Ejecutando por pin válido", this -> numPin, valor);
            digitalWrite(this -> numPin, valor ^ (this -> invertir));
        }
    LOG("FIN PinSalida::setEstado(%d, %d)", this -> numPin, valor);
}

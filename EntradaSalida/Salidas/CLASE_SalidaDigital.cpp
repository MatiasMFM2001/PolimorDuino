#include "CLASE_SalidaDigital.h"

SalidaDigital::SalidaDigital(bool invertir, bool estadoInicial)
    : Salida<bool, 1>(invertir)
    , Pulsable(estadoInicial)
{}

void SalidaDigital::setEstado(bool valor) {
    this -> escribir(valor);
}

#include "CLASE_SalidaDigital.h"

SalidaDigital::SalidaDigital(bool invertir);
    : Salida(invertir)
{}

void SalidaDigital::setEstado(bool valor) {
    this -> escribir(valor);
}

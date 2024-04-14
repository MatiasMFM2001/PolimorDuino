#include "CLASE_SalidaDigital.h"

SalidaDigital::SalidaDigital(bool invertir, bool estadoInicial)
    : Salida<BOOL_1_BIT>(invertir)
    , Pulsable(estadoInicial)
{}

void SalidaDigital::setEstado(bool valor) {
    this -> escribir(valor);
}

size_t SalidaDigital::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "SalidaDigital") + SUPERCLASES_A_JSON(impresora, (Salida<BOOL_1_BIT>), Pulsable);
}

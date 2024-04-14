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

size_t Pulsable::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "Pulsable", estadoActual);
}

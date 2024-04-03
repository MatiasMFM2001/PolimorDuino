#include "CLASE_Pulsable.h"

Pulsable::Pulsable(bool estadoInicial) {
    this -> setEstado(estadoInicial);
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

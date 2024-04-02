#include "CLASE_Pulsable.h"

Pulsable::Pulsable(bool estadoInicial) {
    this -> setEstado(estadoInicial);
}

void Pulsable::encender() {
    this -> setEstado(true);
}

void Pulsable::apagar() {
    this -> setEstado(false);
}

void Pulsable::setEstado(bool valor) {
    if (valor) {
        this -> encender();
    }
    else {
        this -> apagar();
    }
}

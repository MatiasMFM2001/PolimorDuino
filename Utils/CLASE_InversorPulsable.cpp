#include "CLASE_InversorPulsable.h"

InversorPulsable::InversorPulsable(bool invertir, Pulsable *decorado)
    : Pulsable(!invertir, false)
    , decorado(decorado)
{
    this -> setEstado(!invertir);
}

void InversorPulsable::encender(void) {
    this -> decorado -> apagar();
}

void InversorPulsable::apagar(void) {
    this -> decorado -> encender();
} 

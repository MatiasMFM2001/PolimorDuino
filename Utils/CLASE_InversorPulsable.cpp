#include "CLASE_InversorPusable.h"

InversorPulsable::InversorPulsable(bool invertir, Pulsable *decorado)
    : decorado(decorado)
{
    Pulsable::Pulsable(!invertir);
}

void InversorPulsable::encender(void) {
    this -> decorado -> apagar();
}

void InversorPulsable::apagar(void) {
    this -> decorado -> encender();
} 

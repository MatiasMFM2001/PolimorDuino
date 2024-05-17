/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_IniciadorFinito.h"

IniciadorFinito::IniciadorFinito(unsigned long msEntreIniciaciones, unsigned long numIniciaciones, Scheduler* planif, Task *tarea)
    : IniciadorTareas(msEntreIniciaciones, planif, tarea)
    , contIteraciones(Contador<size_t>(numIniciaciones))
{}

bool IniciadorFinito::OnEnable(void) {
    this -> contIteraciones.reiniciar();
    return true;
}

bool IniciadorFinito::deboFinalizar(void) {
    this -> contIteraciones.decrementar(1);
    return (this -> contIteraciones.getValor() == 0);
}

size_t IniciadorFinito::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "IniciadorFinito", contIteraciones);
}

#include "CLASE_IniciadorTareas.h"

IniciadorFinito::IniciadorFinito(unsigned long msEntreIniciaciones, unsigned long numIniciaciones, Scheduler* planif, Task *tarea)
    : IniciadorTareas(msEntreIniciaciones, planif, tarea)
    , contIteraciones(Contador<size_t>(numIniciaciones))
{}

bool IniciadorFinito::OnEnable(void) {
    this -> contIteraciones.reiniciar();
}

bool IniciadorFinito::deboFinalizar(void) {
    this -> contIteraciones.decrementar(1);
    return (this -> contIteraciones.getValor()) == 0);
}

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

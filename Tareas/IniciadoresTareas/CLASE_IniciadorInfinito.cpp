#include "CLASE_IniciadorInfinito.h"

IniciadorInfinito::IniciadorInfinito(unsigned long msEntreIniciaciones, Scheduler* planif, Task *tarea)
    : IniciadorTareas(msEntreIniciaciones, planif, tarea)
{}

bool IniciadorInfinito::deboFinalizar(void) {
    return false;
}

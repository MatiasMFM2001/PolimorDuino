#include "CLASE_IniciadorTareas.h"

IniciadorTareas::IniciadorTareas(unsigned long msEntreIniciaciones, unsigned long numIniciacionesInterno, Scheduler *planif, Task *tarea)
    : Task(msEntreIniciaciones, numIniciacionesInterno, planif, false)
    , tarea(tarea), contIteraciones(Contador<size_t>(numIniciaciones))
{}

bool IniciadorTareas::Callback(void) {
    if ((this -> tarea -> enableIfNot()) && (this -> deboFinalizar())) {
        this -> disable();
    }
    
    return true;
}

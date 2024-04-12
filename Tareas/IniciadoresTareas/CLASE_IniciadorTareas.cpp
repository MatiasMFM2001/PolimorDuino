#include "CLASE_IniciadorTareas.h"
#include "../../Inclusiones/InclusionTaskScheduler.h"

IniciadorTareas::IniciadorTareas(unsigned long msEntreIniciaciones, Scheduler *planif, Task *tarea)
    : Task(msEntreIniciaciones, TASK_FOREVER, planif, false)
    , tarea(tarea)
{}

bool IniciadorTareas::Callback(void) {
    if ((this -> tarea -> enableIfNot()) && (this -> deboFinalizar())) {
        this -> disable();
    }
    
    return true;
}

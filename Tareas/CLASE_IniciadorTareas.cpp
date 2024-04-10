#include "CLASE_IniciadorTareas.h"

IniciadorTareas::IniciadorTareas(unsigned long , size_t numIniciaciones, Scheduler* planif)
    : Task(msEntreIniciaciones, TASK_FOREVER, planif, false)
    , tarea(tarea), contIteraciones(Contador<size_t>(numIniciaciones))
{}

bool IniciadorTareas::OnEnable(void) {
    this -> contIteraciones.reiniciar();
}

bool IniciadorTareas::Callback(void) {
    if (this -> tarea -> enableIfNot()) {
        this -> contIteraciones.decrementar(1);
        
        if ((this -> contIteraciones.getValor()) == 0) {
            this -> disable();
        }
    }
    
    return true;
}

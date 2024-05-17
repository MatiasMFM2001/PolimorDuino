/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_IniciadorTareas.h"
#include "../../Inclusiones/InclusionTaskSchedulerDeclarations.h"

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

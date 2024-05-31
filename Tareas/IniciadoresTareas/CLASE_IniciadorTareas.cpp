/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_IniciadorTareas.h"
#include "../../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include "../../Inclusiones/InclusionLog4Arduino.h"

IniciadorTareas::IniciadorTareas(const char *nombre, unsigned long msEntreIniciaciones, Scheduler *planif, Task *tarea)
    : Task(msEntreIniciaciones, TASK_FOREVER, planif, false)
    , tarea(tarea), nombre(nombre)
{}

bool IniciadorTareas::Callback(void) {
    LOG("INICIO IniciadorTareas::Callback('%s')", this -> nombre);

    if (!(this -> tarea -> isEnabled())) {
        if (this -> deboFinalizar()) {
            LOG("IniciadorTareas::Callback('%s') - Me deshabilito", this -> nombre);
            this -> disable();
        }
        else {
            LOG("IniciadorTareas::Callback('%s') - Habilito mi tarea", this -> nombre);
            this -> tarea -> restart();
        }
    }
    else {
        LOG("IniciadorTareas::Callback('%s') - No hago nada, la tarea ya estaba habilitada", this -> nombre);
    }
    
    LOG("FIN IniciadorTareas::Callback('%s')", this -> nombre);
    return true;
}

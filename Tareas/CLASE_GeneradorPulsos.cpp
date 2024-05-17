/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_GeneradorPulsos.h"
#include "../Utils/FuncionesGlobales.h"
#include "../Inclusiones/InclusionLog4Arduino.h"
#include "../Logger/FuncionesJSON.h"
//#include "CLASE_WrapperPuntero"

GeneradorPulsos::GeneradorPulsos
    (Pulsable* pulsable, long msSemiCiclo, long numPulsos, Scheduler* planif)
    : Task(msSemiCiclo, multiplicarNumIteraciones(numPulsos, 2), planif, false)
    , pulsable(pulsable)
{}

void GeneradorPulsos::enableNumPulsos(long cant) {
    LOG("EJECUTANDO GeneradorPulsos::enableNumPulsos(%ld)", cant);
    Task::setIterations(multiplicarNumIteraciones(cant, 2));
    Task::enable();
}

void GeneradorPulsos::enablePeriodo(long ms) {
    LOG("EJECUTANDO GeneradorPulsos::enablePeriodo(%ld ms)", ms);
    Task::setInterval(ms / 2);
    Task::enable();
}

void GeneradorPulsos::enableFrecuencia(long hz) {
    LOG("INICIO GeneradorPulsos::enableFrecuencia(%ld)", hz);
        if (hz == 0) {
            LOG("GeneradorPulsos::enableFrecuencia(%ld) - Saliendo porque hz == 0", hz);
            Task::disable();
            
            return;
        }
        
        this -> enablePeriodo(TASK_SECOND / hz);
    LOG("FIN GeneradorPulsos::enableFrecuencia(%ld)", hz);
}


bool GeneradorPulsos::OnEnable(void) {
    FLOGS("EJECUTANDO GeneradorPulsos::OnEnable()");
    this -> pulsable -> apagar();
    return true;
}

bool GeneradorPulsos::Callback(void) {
    LOG("INICIO GeneradorPulsos::Callback(), iteraci�n %d", Task::getRunCounter());
        this -> pulsable -> setEstado(!esPar(Task::getRunCounter()));
    FLOGS("FIN GeneradorPulsos::Callback()");
        
    return true;
}

void GeneradorPulsos::OnDisable(void) {
    FLOGS("EJECUTANDO GeneradorPulsos::OnDisable()");
    this -> pulsable -> apagar();
}

size_t GeneradorPulsos::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "GeneradorPulsos", pulsable);
}

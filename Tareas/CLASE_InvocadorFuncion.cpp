/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_InvocadorFuncion.h"
  
InvocadorFuncion::InvocadorFuncion(long msEntreLlamados, long numLlamados, Scheduler *planif, void (*callback)(void), bool habilitar)
    : Task(msEntreLlamados, numLlamados, planif, habilitar)
    , callback(callback)
{}

bool InvocadorFuncion::Callback(void) {
    if (this -> callback) {
        this -> callback();
    }
    
    return true;
}

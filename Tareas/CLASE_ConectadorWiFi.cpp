/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_ConectadorWiFi.h"
#include <Arduino.h>
#include "../Inclusiones/InclusionLog4Arduino.h"

ConectadorWiFi::ConectadorWiFi(long msEntreLlamados, Scheduler *planif, CallbackResultado<WiFiClass &> *notificadorConexionExitosa)
    : Task(msEntreLlamados, TASK_FOREVER, planif, false)
    , notificadorConexionExitosa(notificadorConexionExitosa)
{}

void ConectadorWiFi::inicializar(void) {
    Task::enable();
    WiFi.begin(this -> nombreRed, this -> contrasenia);
}

void ConectadorWiFi::setCredenciales(char *nombreRed, char *contrasenia) {
    this -> nombreRed = nombreRed;
    this -> contrasenia = contrasenia;
}

bool ConectadorWiFi::Callback(void) {
    LOG("EJECUTANDO ConectadorWiFi::Callback()");
    
    if (WiFi.status() == WL_CONNECTED) {
        this -> notificadorConexionExitosa -> notificar(WiFi);
        Task::disable();
    }

    return true;
}

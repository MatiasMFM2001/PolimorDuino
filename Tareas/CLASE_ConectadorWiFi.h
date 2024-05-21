/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONECTADOR_WIFI
#define CONECTADOR_WIFI

#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include "../Utils/INTERFAZ_Inicializable.h"
#include <WiFi.h>
#include "../Medidores/INTERFAZ_CallbackResultado.h"
    class ConectadorWiFi : public Task, public Inicializable {
        private:
            CallbackResultado<WiFiClass &> *notificadorConexionExitosa;
            char *nombreRed;
            char *contrasenia;
        
        public:
            /**
             * @brief Construye un ConectadorWiFi...
             */
            ConectadorWiFi(long msEntreLlamados, Scheduler *planif, CallbackResultado<WiFiClass &> *notificadorConexionExitosa);
        
            void inicializar(void) override;
            void setCredenciales(char *nombreRed, char *contrasenia);
        
            /**
             * @brief Ejecuta la impresión periódica.
             *
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override;
    };
#endif

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONECTADOR_WIFI
#define CONECTADOR_WIFI

#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include "../Utils/INTERFAZ_Inicializable.h"
    class ConectadorWiFi : public Task, public Inicializable {
        private:
            CallbackResultado<WiFiClass &> *notificadorConexionExitosa;
            char *nombreRed;
            char *contrasenia;
        
        public:
            /**
             * @brief Construye un AutoFlusher, con la impresora, tiempo de
             *  espera y scheduler especificados.
             * 
             * @param impresora La impresora especificada (que no debería ser
             *  nula).
             * @param msEntreLlamados La cantidad mínima de milisegundos a
             *  esperar entre una impresión y la siguiente.
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             */
            ConectadorWiFi(long msEntreLlamados, Scheduler *planif, CallbackResultado<void *> *notificadorConexionExitosa, char *nombreRed, char *contrasenia);
        
            void inicializar(void) override;
        
            /**
             * @brief Ejecuta la impresión periódica.
             *
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override;
    };
#endif

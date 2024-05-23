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
#include "../Utils/FuncionesGlobales.h"
    template <size_t TAMANIO_NOMBRE = 32, size_t TAMANIO_CONTRASENIA = 32>
    class ConectadorWiFi : public Task, public Inicializable {
        private:
            CallbackResultado<WiFiClass> *notificadorConexionExitosa;
            Array<char, TAMANIO_NOMBRE + 1> nombreRed;
            Array<char, TAMANIO_CONTRASENIA + 1> contrasenia;
        
        public:
            /**
             * @brief Construye un ConectadorWiFi...
             */
            ConectadorWiFi(long msEntreLlamados, Scheduler *planif, CallbackResultado<WiFiClass> *notificadorConexionExitosa)
                : Task(msEntreLlamados, TASK_FOREVER, planif, false)
                , notificadorConexionExitosa(notificadorConexionExitosa), nombreRed(Array<char, TAMANIO_NOMBRE + 1>()), contrasenia(Array<char, TAMANIO_CONTRASENIA + 1>())
            {}
        
            void inicializar(void) override {
                Task::enable();
                WiFi.begin(this -> nombreRed.data(), this -> contrasenia.data());
            }
            
            void setCredenciales(const char *nombreRed, const char *contrasenia) {
                agregarFinalArrayTerminado(nombreRed, this -> nombreRed, '\0', true);
                agregarFinalArrayTerminado(contrasenia, this -> contrasenia, '\0', true);
            }
        
            /**
             * @brief Ejecuta la impresión periódica.
             *
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override {
                LOG("EJECUTANDO ConectadorWiFi::Callback()");
                
                if (WiFi.status() == WL_CONNECTED) {
                    this -> notificadorConexionExitosa -> notificar(WiFi);
                    Task::disable();
                }

                return true;
            }
    };
#endif

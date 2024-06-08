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
#include "../Medidores/Callbacks/INTERFAZ_CallbackResultado.h"
#include "../Utils/FuncionesGlobales.h"
#include "../Utils/CLASE_StringEstatica.h"
    template <size_t TAMANIO_NOMBRE = 32, size_t TAMANIO_CONTRASENIA = 32>
    class ConectadorWiFi : public Task, public Inicializable {
        private:
            CallbackResultado<WiFiClass> *notificadorConexionExitosa;
            StringEstatica<TAMANIO_NOMBRE> nombreRed;
            StringEstatica<TAMANIO_CONTRASENIA> contrasenia;
        
        public:
            /**
             * @brief Construye un ConectadorWiFi...
             */
            ConectadorWiFi(long msEntreLlamados, Scheduler *planif, CallbackResultado<WiFiClass> *notificadorConexionExitosa)
                : Task(msEntreLlamados, TASK_FOREVER, planif, false)
                , notificadorConexionExitosa(notificadorConexionExitosa), nombreRed(StringEstatica<TAMANIO_NOMBRE>()), contrasenia(StringEstatica<TAMANIO_CONTRASENIA>())
            {}
        
            void inicializar(void) override {
                #ifdef ESP8266
                    WiFi.setAutoConnect(true);
                #endif
            
                WiFi.mode(WIFI_STA);
                WiFi.begin(this -> nombreRed.getContenido(), this -> contrasenia.getContenido());
                
                Task::enable();
            }
            
            void setCredenciales(const char *nombreRed, const char *contrasenia, bool inicializarSiValido = true) {
                this -> nombreRed.agregarFinal(nombreRed);
                this -> contrasenia.agregarFinal(contrasenia);
                
                if (inicializarSiValido && !(this -> nombreRed.estaVacia()) && !(this -> contrasenia.estaVacia())) {
                    this -> inicializar();
                }
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

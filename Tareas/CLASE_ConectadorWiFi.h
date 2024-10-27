/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONECTADOR_WIFI
#define CONECTADOR_WIFI

#ifdef ESP8266
    #include <ESP8266WiFi.h>
    typedef ESP8266WiFiClass WiFiClass;
#else
    #include <WiFi.h>
#endif

#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include "../Utils/INTERFAZ_Inicializable.h"
#include "../Utils/Pulsables/CLASE_Pulsable.h"
#include "../Utils/FuncionesGlobales.h"
#include "../Utils/EstructurasDatos/Cadenas/CLASE_StringEstatica.h"
    template <size_t TAMANIO_NOMBRE = 32, size_t TAMANIO_CONTRASENIA = 32>
    class ConectadorWiFi : public Task, public Inicializable {
        private:
            Pulsable *notificadorEstadosConexion;
            bool conexionNotificada;
            
            StringEstatica<TAMANIO_NOMBRE> nombreRed;
            StringEstatica<TAMANIO_CONTRASENIA> contrasenia;
        
        public:
            /**
             * @brief Construye un ConectadorWiFi...
             */
            ConectadorWiFi(long msEntreLlamados, Scheduler *planif, Pulsable *notificadorEstadosConexion)
                : Task(msEntreLlamados, TASK_FOREVER, planif, false)
                , notificadorEstadosConexion(notificadorEstadosConexion), nombreRed(StringEstatica<TAMANIO_NOMBRE>()), contrasenia(StringEstatica<TAMANIO_CONTRASENIA>()), conexionNotificada(false)
            {}
        
            void inicializar(void) override {
                #ifdef ESP8266
                    WiFi.setAutoConnect(true);
                #endif
            
                WiFi.mode(WIFI_STA);
                
                #if (defined(ARDUINO_ARCH_RP2040) && !defined(__MBED__))
                    cyw43_wifi_pm(&cyw43_state, CYW43_PERFORMANCE_PM);
                #endif
                
                WiFi.begin(this -> nombreRed.getContenido(), this -> contrasenia.getContenido()); 
                Task::enable();
            }
            
            void setCredenciales(const char *nombreRed, const char *contrasenia, bool inicializarSiValido = false) {
                this -> nombreRed.agregarFinal(nombreRed);
                this -> contrasenia.agregarFinal(contrasenia);
                
                if (inicializarSiValido && !(this -> nombreRed.estaVacia()) && !(this -> contrasenia.estaVacia())) {
                    this -> inicializar();
                }
            }
        
            /**
             * @brief Ejecuta la comprobación periódica.
             *
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override {
                CLOG_REFERENCIA_IMPRESORA(Serial, F("EJECUTANDO ConectadorWiFi::Callback()"));
                
                switch (WiFi.status()) {
                    case WL_NO_SHIELD:
                        CLOG_REFERENCIA_IMPRESORA(Serial, F("ConectadorWiFi::Callback() - No hay placas WiFi conectadas. Deshabilitando tarea"));
                        
                        Task::disable();
                        break;
                        
                    case WL_NO_SSID_AVAIL:
                        CLOG_REFERENCIA_IMPRESORA(Serial, F("ConectadorWiFi::Callback() - No se encontró la red"), this -> nombreRed.getContenido());
                        break;
                    
                    case WL_CONNECTED:
                        CLOG_REFERENCIA_IMPRESORA(Serial, F("ConectadorWiFi::Callback() - Conexión exitosa a la red"), this -> nombreRed.getContenido(), F("con IP:"), WiFi.localIP());
                        
                        if (!(this -> conexionNotificada) && (this -> notificadorEstadosConexion)) {
                            this -> notificadorEstadosConexion -> encender();
                            this -> conexionNotificada = true;
                        }
                        
                        break;
                        
                    case WL_CONNECT_FAILED:
                        CLOG_REFERENCIA_IMPRESORA(Serial, F("ConectadorWiFi::Callback() - Conexión fallida a la red"), this -> nombreRed.getContenido());
                        break;
                        
                    case WL_CONNECTION_LOST:
                        CLOG_REFERENCIA_IMPRESORA(Serial, F("ConectadorWiFi::Callback() - Conexión perdida a la red"), this -> nombreRed.getContenido());
                        
                        if (this -> notificadorEstadosConexion) {
                            this -> notificadorEstadosConexion -> apagar();
                            this -> conexionNotificada = false;
                        }
                        
                        break;
                        
                    case WL_DISCONNECTED:
                        CLOG_REFERENCIA_IMPRESORA(Serial, F("ConectadorWiFi::Callback() - Desconectado"));
                        break;
                    
                    default:
                        break;
                }

                return true;
            }
    };
#endif

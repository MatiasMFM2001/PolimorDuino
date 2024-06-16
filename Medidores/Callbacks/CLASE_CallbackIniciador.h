/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CALLBACK_INICIADOR
#define CALLBACK_INICIADOR

#include <Printable.h>
#include "../../Inclusiones/InclusionLog4Arduino.h"
    template <typename... T>
    class CallbackIniciador: public CallbackResultado<T...> {
        private:
            Task *tarea;
            CallbackResultado<T...> *accionesAdicionales;
            const char *nombre;
        
        public:
            CallbackIniciador(const char *nombre, Task *tarea, CallbackResultado<T...> *accionesAdicionales = nullptr)
                : tarea(tarea), accionesAdicionales(accionesAdicionales), nombre(nombre)
            {}
            
            void notificar(T&... resultado) override {
                LOG("INICIO CallbackIniciador::notificar('%s')", this -> nombre);
                
                if (this -> tarea -> isEnabled()) {
                    LOG("CallbackIniciador::notificar('%s') - Saliendo porque la tarea ya estaba habilitada", this -> nombre);
                    return;
                }
                
                LOG("CallbackIniciador::notificar('%s') - Reiniciando tarea", this -> nombre);
                this -> tarea -> restart();
                
                if (this -> accionesAdicionales) {
                    LOG("CallbackIniciador::notificar('%s') - Ejecutando callback con acciones adicionales", this -> nombre);
                    this -> accionesAdicionales -> notificar(resultado...);
                }
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "CallbackIniciador", accionesAdicionales);
            }
    };
#endif

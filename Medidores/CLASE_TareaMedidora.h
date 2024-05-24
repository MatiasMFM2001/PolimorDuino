/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TAREA_MEDIDORA
#define TAREA_MEDIDORA

#include "CLASE_Medidor.h"
#include "../Inclusiones/InclusionTaskScheduler.h"
#include "INTERFAZ_CondicionResultado.h"
    /**
     * @brief 
     * 
     * @tparam T_RESULTADO El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&) = imprimir>
    class TareaMedidora : public Medidor<T_RESULTADO, F_LOGGER>, public Task {
        private:
            CondicionResultado<T_RESULTADO> *verificador;
        
        public:
            TareaMedidora(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, unsigned long msMedicion, Scheduler *planif, CondicionResultado<T_RESULTADO> *verificador)
                : Medidor<T_RESULTADO, F_LOGGER>(nombre, callback)
                , Task(msMedicion, TASK_ONCE, planif, false), verificador(verificador)
            {}
            
            bool OnEnable(void) override {
                this -> iniciarMedicion();
                return true;
            }
            
            virtual T_RESULTADO getResultado() = 0;
            
            /**
             * @brief Obtiene el resultado y finaliza la medición actual.
             * 
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override {
                T_RESULTADO resultado = this -> getResultado();
                
                if (!(this -> verificador) || (this -> verificador -> esValido(resultado))) {
                    this -> finalizarMedicion(resultado);
                }
                
                return true;
            }
    };
#endif

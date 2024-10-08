/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TAREA_MEDIDORA
#define TAREA_MEDIDORA

#include "CLASE_Medidor.h"
#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"
    /**
     * @brief 
     * 
     * @tparam T_RESULTADO El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&) = imprimir>
    class TareaMedidora : public Medidor<T_RESULTADO, F_LOGGER>, public Task {
        public:
            TareaMedidora(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, unsigned long msMedicion, Scheduler *planif, CondicionResultado<T_RESULTADO> *verificador)
                : Medidor<T_RESULTADO, F_LOGGER>(nombre, callback, verificador)
                , Task(msMedicion, TASK_ONCE, planif, false)
            {}
            
            bool OnEnable(void) override {
                LOG("TareaMedidora::OnEnable('%s')", this -> nombre);
                this -> iniciarMedicion();
                
                return true;
            }
            
            virtual T_RESULTADO getResultado(void) = 0;
            
            /**
             * @brief Obtiene el resultado y finaliza la medición actual.
             * 
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override {
                LOG("TareaMedidora::Callback('%s', %d)", this -> nombre, Task::getRunCounter());
                T_RESULTADO resultado = this -> getResultado();
                this -> finalizarMedicion(resultado);
                
                return true;
            }
            
            void OnDisable(void) override {
                LOG("TareaMedidora::OnDisable('%s')", this -> nombre);
            }
    };
#endif

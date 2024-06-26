/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FRECUENCIMETRO
#define FRECUENCIMETRO

#include "../../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include "../../Utils/CLASE_Contador.h"
#include "CLASE_MedidorTemporizado.h"
    /**
     * @brief Tarea que permite medir la frecuencia de una forma de onda
     *  periódica, a partir de la cantidad de flancos por segundo.
     */
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&) = imprimir>
    class Frecuencimetro : public MedidorTemporizado<T_RESULTADO, F_LOGGER> {
        private:
            /** @brief Contador de flancos transitados. */
            Contador<T_RESULTADO> contFrec;
    
        public:
            /**
             * @brief Construye un Frecuencimetro, con el scheduler especificado.
             * 
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             * @param nombre El nombre del medidor (que no debería ser nulo).
             */
            Frecuencimetro(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, Scheduler *planif, CondicionResultado<T_RESULTADO> *verificador = nullptr)
                : MedidorTemporizado<T_RESULTADO, F_LOGGER>(nombre, callback, TASK_SECOND, planif, verificador)
                , contFrec(Contador<T_RESULTADO>(0))
            {}

            /**
             * @brief Reinicia el contador de flancos transitados.
             */
            virtual void iniciarMedicion(void) override {
                this -> contFrec.reiniciar();
            }
            
            /**
             * @brief Incrementa en 1 el contador de flancos transitados.
             */
            void incrementar(void) {
                if (!(this -> isEnabled())) {
                    return;
                }
                
                this -> contFrec.incrementar(1);
            }

            /**
             * @returns El valor de la última medición realizada, en Hz.
             */
            virtual T_RESULTADO getResultado(void) override {
                return (this -> contFrec.getValor());
            }
            
            /**
             * @returns @c true si el contador vale 0, @c false en caso
             *  contrario.
             */
            bool estaEnCero(void) {
                return (this -> contFrec.estaEn(0));
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "Frecuencimetro", contFrec) + SUPERCLASES_A_JSON(impresora, (MedidorTemporizado<T_RESULTADO, F_LOGGER>));
            }
    };
#endif

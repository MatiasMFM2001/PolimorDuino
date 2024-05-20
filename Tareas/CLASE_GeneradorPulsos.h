/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GENERADOR_PULSOS
#define GENERADOR_PULSOS

#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include "../Utils/Pulsables/CLASE_Pulsable.h"
#include <Printable.h>
    /**
     * @brief Tarea que permite generar una cantidad de pulsos determinada, a
     *  una determinada frecuencia, con ~50% de ancho de pulso.
     */
    class GeneradorPulsos : public Task, public Printable {
        private:
            /** @brief Puntero al objeto encendible y apagable. */
            Pulsable *pulsable;
    
        public:
            /**
             * @brief Construye un GeneradorPulsos, con el objeto pulsable,
             *  el período de un semiciclo, la cantidad de pulsos, y el
             *  scheduler especificados.
             * 
             * @param pulsable Puntero al objeto sobre el cual se generarán los
             *  pulsos.
             * @param msSemiCiclo La cantidad mínima de milisegundos a usar
             *  como período de los pulsos
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             */
            GeneradorPulsos(Pulsable *pulsable, long msSemiCiclo, long numPulsos, Scheduler *planif);
    
            /**
             * @brief Habilita la tarea para su ejecución, estableciendo la
             *  cantidad de pulsos a emitir.
             * 
             * @param cant La cantidad de pulsos a emitir.
             */
            void enableNumPulsos(long cant);
            
            /**
             * @brief Habilita la tarea para su ejecución, estableciendo el
             *  período de los pulsos a emitir.
             * 
             * @param ms La cantidad mínima de milisegundos a usar
             *  como período de los pulsos.
             */
            void enablePeriodo(long ms);
            
            /**
             * @brief Habilita la tarea para su ejecución, estableciendo la
             *  frecuencia de los pulsos a emitir.
             * 
             * @param hz La frecuencia aproximada de los pulsos.
             */
            void enableFrecuencia(long hz);
        
            /**
             * @brief Apaga el objeto pulsable.
             * 
             * @returns @c true para indicar que la tarea debería permanecer
             *  habilitada.
             */
            bool OnEnable(void) override;

            /**
             * @brief Ejecuta la oscilación periódica.
             * 
             * @returns @c true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override;
            
            /**
             * @brief Apaga el objeto pulsable.
             */
            void OnDisable(void) override;
        
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             * 
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override;
    };
#endif

#ifndef FRECUENCIMETRO
#define FRECUENCIMETRO

#include "InclusionTaskSchedulerDeclarations.h"
#include "CLASE_Contador.h"
	/**
     * @brief Tarea que permite medir la frecuencia de una forma de onda
     *  periódica, a partir de la cantidad de flancos por segundo.
     */
    class Frecuencimetro : public Task {
        private:
			/** @brief Contador de flancos transitados. */
            Contador<unsigned short> contFrec;
            
            /** @brief Último valor de frecuencia medido. */
            unsigned short ultFrec;
    
        public:
            /**
             * @brief Construye un Frecuencimetro, con el scheduler especificado.
             * 
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             */
            Frecuencimetro(Scheduler* planif);

            /**
             * @brief De forma periódica, finaliza la medición actual e inicia
             *  una nueva.
             * 
             * @returns @code true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback() override;

            /**
             * @brief Reinicia el contador de flancos transitados.
             */
            void reiniciar();
            
            /**
             * @brief Incrementa en 1 el contador de flancos transitados.
             */
            void incrementar();

            /**
             * @returns El valor de la última medición realizada, en Hz.
             */
            unsigned short getHz();
            
            /**
             * @returns @code true si el contador vale 0, @code false en caso
             *  contrario.
             */
            bool estaEnCero();
    };
#endif

#ifndef FRECUENCIMETRO
#define FRECUENCIMETRO

#include "InclusionTaskSchedulerDeclarations.h"
#include "CLASE_Contador.h"
	/**
     * @brief Tarea que permite medir la frecuencia de una forma de onda
     *  periódica, a partir de la cantidad de flancos por segundo.
     */
    class Frecuencimetro : public Task, public MedidorTemporizado<unsigned short> {
        private:
			/** @brief Contador de flancos transitados. */
            Contador<unsigned short> contFrec;
    
        public:
            /**
             * @brief Construye un Frecuencimetro, con el scheduler especificado.
             * 
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             * @param nombre El nombre del medidor (que no debería ser nulo).
             */
            Frecuencimetro(Scheduler* planif, const __FlashStringHelper *nombre);

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
            virtual void iniciarMedicion() override;
            
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

#ifndef FRECUENCIMETRO
#define FRECUENCIMETRO

#include "InclusionTaskSchedulerDeclarations.h"
#include "CLASE_Contador.h"
	/**
     * @brief Tarea que permite medir la frecuencia de una forma de onda
     *  periódica, a partir de la cantidad de flancos por segundo.
     */
    template <typename TResultado, void (*FLogger)(TResultado&)>
    class Frecuencimetro : public MedidorTemporizado<TResultado, FLogger> {
        private:
			/** @brief Contador de flancos transitados. */
            Contador<TResultado> contFrec;
    
        public:
            /**
             * @brief Construye un Frecuencimetro, con el scheduler especificado.
             * 
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             * @param nombre El nombre del medidor (que no debería ser nulo).
             */
            Frecuencimetro(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback, Scheduler* planif)
                : MedidorTemporizado(nombre, callback, TASK_SECOND, planif)
                , contFrec(Contador<TResultado>(0))
            {}

            /**
             * @brief De forma periódica, finaliza la medición actual e inicia
             *  una nueva.
             * 
             * @returns @code true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback() override {
                this -> finalizarMedicion(this -> getResultado());
                return true;
            }

            /**
             * @brief Reinicia el contador de flancos transitados.
             */
            virtual void iniciarMedicion() override {
                this -> contFrec.reiniciar();
            }
            
            /**
             * @brief Incrementa en 1 el contador de flancos transitados.
             */
            void incrementar() {
                if (!(this -> isEnabled())) {
                    return;
                }
                
                this -> contFrec.incrementar(1);
            }

            /**
             * @returns El valor de la última medición realizada, en Hz.
             */
            virtual TResultado getResultado() override {
                return (this -> contFrec.getValor());
            }
            
            /**
             * @returns @code true si el contador vale 0, @code false en caso
             *  contrario.
             */
            bool estaEnCero() {
                return (this -> getResultado()) == 0;
            }
    };
#endif

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
                : MedidorTemporizado<TResultado, FLogger>(nombre, callback, TASK_SECOND, planif)
                , contFrec(Contador<TResultado>(0))
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
            virtual TResultado getResultado(void) override {
                return (this -> contFrec.getValor());
            }
            
            /**
             * @returns @code true si el contador vale 0, @code false en caso
             *  contrario.
             */
            bool estaEnCero(void) {
                return (this -> getResultado()) == 0;
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print& impresora) const override {
                return OBJETO_A_JSON(impresora, "Frecuencimetro", TResultado, contFrec) + SUPERCLASES_A_JSON(impresora, MedidorTemporizado<TResultado, FLogger>);
            }
    };
#endif

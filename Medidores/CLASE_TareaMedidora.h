#ifndef TAREA_MEDIDORA
#define TAREA_MEDIDORA

#include "CLASE_Medidor.h"
    /**
     * @brief 
     * 
     * @tparam TResultado El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename TResultado, void (*FLogger)(TResultado&)>
    class TareaMedidora : public Medidor<TResultado, FLogger>, public Task {
        public:
            TareaMedidora(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback, unsigned long msMedicion, Scheduler* planif)
                : Medidor<TResultado, FLogger>(nombre, callback)
                , Task(msMedicion, TASK_ONCE, planif, false)
            {}
            
            bool OnEnable(void) override {
                this -> iniciarMedicion();
                return true;
            }
            
            virtual TResultado getResultado() = 0;
            
            /**
             * @brief Obtiene el resultado y finaliza la medición actual.
             * 
             * @returns @code true para indicar que la ejecución de la tarea fue
             *  "productiva".
             */
            bool Callback(void) override {
                this -> finalizarMedicion(this -> getResultado());
                return true;
            }
    };
#endif

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
                : Medidor(nombre, callback)
                , Task(msMedicion, TASK_ONCE, planif, false)
            {}
            
            void OnEnable() override {
                this -> iniciarMedicion();
            }
            
            virtual TResultado getResultado() = 0;
            
            bool Callback() override {
                this -> finalizarMedicion(this -> getResultado());
                return true;
            }
    };
#endif

#ifndef MEDIDOR_INSTANTANEO
#define MEDIDOR_INSTANTANEO

#include "../CLASE_TareaMedidora.h"
    /**
     * @brief 
     * 
     * @tparam TResultado El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename TResultado, void (*FLogger)(TResultado&)>
    class MedidorInstantaneo : public TareaMedidora<TResultado, FLogger> {
        public:
            MedidorInstantaneo(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback, Scheduler *planif)
                : TareaMedidora<TResultado, FLogger>(nombre, callback, TASK_MILLISECOND, planif)
            {}
        
            virtual void iniciarMedicion(void) override {
            }
    };
#endif

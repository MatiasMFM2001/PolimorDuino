#ifndef MEDIDOR_INSTANTANEO
#define MEDIDOR_INSTANTANEO

#include "../CLASE_TareaMedidora.h"
    /**
     * @brief 
     * 
     * @tparam T_RESULTADO El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&)>
    class MedidorInstantaneo : public TareaMedidora<T_RESULTADO, F_LOGGER> {
        public:
            MedidorInstantaneo(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, Scheduler *planif)
                : TareaMedidora<T_RESULTADO, F_LOGGER>(nombre, callback, TASK_MILLISECOND, planif)
            {}
        
            virtual void iniciarMedicion(void) override {
            }
    };
#endif

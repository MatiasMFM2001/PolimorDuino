#ifndef MEDIDOR_INSTANTANEO
#define MEDIDOR_INSTANTANEO

#include "CLASE_Medidor.h"
    /**
     * @brief 
     * 
     * @tparam TResultado El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename TResultado>
    class MedidorInstantaneo : public Medidor<TResultado> {
        public:
            MedidorInstantaneo(const __FlashStringHelper *nombre)
                : Medidor(nombre)
            {}
        
            virtual void iniciarMedicion() override {
            }
    };
#endif

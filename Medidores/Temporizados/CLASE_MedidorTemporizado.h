#ifndef MEDIDOR_TEMPORIZADO
#define MEDIDOR_TEMPORIZADO

#include "CLASE_Medidor.h"
    /**
     * @brief 
     * 
     * @tparam TResultado El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename TResultado>
    class MedidorTemporizado : public Medidor<TResultado> {
        public:
            MedidorInstantaneo(const __FlashStringHelper *nombre)
                : Medidor(nombre)
            {}
    };
#endif

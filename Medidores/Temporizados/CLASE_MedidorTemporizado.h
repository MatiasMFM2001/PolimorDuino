#ifndef MEDIDOR_TEMPORIZADO
#define MEDIDOR_TEMPORIZADO

#include "CLASE_TareaMedidora.h"
    /**
     * @brief 
     * 
     * @tparam TResultado El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename TResultado, void (*FLogger)(TResultado&)>
    class MedidorTemporizado : public TareaMedidora<TResultado, FLogger> {
        public:
            MedidorTemporizado(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback, unsigned long msMedicion, Scheduler* planif)
                : TareaMedidora<TResultado, FLogger>(nombre, callback, msMedicion, planif)
            {}
    };
#endif

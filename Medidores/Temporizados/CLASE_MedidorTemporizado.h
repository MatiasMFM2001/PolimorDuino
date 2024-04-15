#ifndef MEDIDOR_TEMPORIZADO
#define MEDIDOR_TEMPORIZADO

#include "CLASE_TareaMedidora.h"
    /**
     * @brief 
     * 
     * @tparam T_RESULTADO El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&)>
    class MedidorTemporizado : public TareaMedidora<T_RESULTADO, F_LOGGER> {
        public:
            MedidorTemporizado(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, unsigned long msMedicion, Scheduler *planif)
                : TareaMedidora<T_RESULTADO, F_LOGGER>(nombre, callback, msMedicion, planif)
            {}
    };
#endif

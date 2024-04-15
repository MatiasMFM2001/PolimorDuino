#ifndef SALIDA_PWM
#define SALIDA_PWM

#include "CLASE_SalidaContinua.h"
    template <typename T, byte N_NUM_BITS>
    class SalidaPWM : public SalidaContinua<T, N_NUM_BITS> {
        public:
            SalidaPWM(bool invertir)
                : SalidaContinua<T, N_NUM_BITS>(invertir)
            {}
    };
#endif

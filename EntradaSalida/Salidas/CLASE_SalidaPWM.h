#ifndef SALIDA_PWM
#define SALIDA_PWM

#include "CLASE_SalidaContinua.h"
    template <typename T, byte NumBits>
    class SalidaPWM : SalidaContinua<T, NumBits> {    
        public:
            SalidaPWM(bool invertir)
                : SalidaContinua(invertir)
            {}
    };
#endif

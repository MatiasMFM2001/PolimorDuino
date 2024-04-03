#ifndef SALIDA_ANALOGICA
#define SALIDA_ANALOGICA

#include "CLASE_SalidaContinua.h"
    template <typename T, byte NumBits>
    class SalidaAnalogica : SalidaContinua<T, NumBits> {    
        public:
            SalidaAnalogica(bool invertir)
                : SalidaContinua(invertir)
            {}
    };
#endif

#ifndef SALIDA_ANALOGICA
#define SALIDA_ANALOGICA

#include "CLASE_SalidaContinua.h"
    template <typename T, byte N_NUM_BITS>
    class SalidaAnalogica : public SalidaContinua<T, N_NUM_BITS> {
        public:
            SalidaAnalogica(bool invertir)
                : SalidaContinua<T, N_NUM_BITS>(invertir)
            {}
    };
#endif

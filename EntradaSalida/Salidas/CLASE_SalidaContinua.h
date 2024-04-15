#ifndef SALIDA_CONTINUA
#define SALIDA_CONTINUA

#include "CLASE_Salida.h"
    template <typename T, byte N_NUM_BITS>
    class SalidaContinua : public Salida<T, N_NUM_BITS> {
        public:
            SalidaContinua(bool invertir)
                : Salida<T, N_NUM_BITS>(invertir)
            {}
    };
#endif

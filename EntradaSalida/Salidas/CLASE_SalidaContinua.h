#ifndef SALIDA_CONTINUA
#define SALIDA_CONTINUA

#include "CLASE_Salida.h"
    template <typename T, byte NumBits>
    class SalidaContinua : public Salida<T, NumBits> {
        public:
            SalidaContinua(bool invertir)
                : Salida(invertir)
            {}
    };
#endif

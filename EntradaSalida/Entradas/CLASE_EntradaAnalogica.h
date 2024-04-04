#ifndef ENTRADA_ANALOGICA
#define ENTRADA_ANALOGICA

#include "CLASE_Entrada.h"
    template <typename T, byte NumBits>
    class EntradaAnalogica : public Entrada<T, NumBits> {
        public:
            EntradaAnalogica(bool invertir)
                : Entrada(invertir)
            {}
    };
#endif

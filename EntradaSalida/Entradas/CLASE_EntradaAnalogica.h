#ifndef ENTRADA_ANALOGICA
#define ENTRADA_ANALOGICA

#include "CLASE_Entrada.h"
    template <typename T, byte N_NUM_BITS>
    class EntradaAnalogica : public Entrada<T, N_NUM_BITS> {
        public:
            EntradaAnalogica(bool invertir)
                : Entrada<T, N_NUM_BITS>(invertir)
            {}
    };
#endif

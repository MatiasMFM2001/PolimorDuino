#ifndef ESTRATEGIA_PADDING
#define ESTRATEGIA_PADDING

#include <Array.h>
    template <size_t NumDigitos>
    class EstrategiaPadding {
        public:
            virtual void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) = 0;
    };
#endif

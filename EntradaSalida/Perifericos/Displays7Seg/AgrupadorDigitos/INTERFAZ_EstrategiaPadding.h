#ifndef ESTRATEGIA_PADDING
#define ESTRATEGIA_PADDING

#include <Array.h>
    template <size_t NumDigitos>
    class EstrategiaPadding {
        public:
            void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida);
    };
#endif

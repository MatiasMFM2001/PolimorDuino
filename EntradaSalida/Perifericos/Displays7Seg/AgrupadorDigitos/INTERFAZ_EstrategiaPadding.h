#ifndef ESTRATEGIA_PADDING
#define ESTRATEGIA_PADDING

#define DISPLAY7SEG_APAGADO ((byte) 255)

#include <Array.h>
#include <Printable.h>
    template <size_t NumDigitos>
    class EstrategiaPadding : public Printable {
        public:
            virtual void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) = 0;
    };
#endif

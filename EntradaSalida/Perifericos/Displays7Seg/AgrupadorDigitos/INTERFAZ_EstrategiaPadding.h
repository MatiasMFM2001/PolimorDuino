#ifndef ESTRATEGIA_PADDING
#define ESTRATEGIA_PADDING

#define DISPLAY7SEG_APAGADO ((byte) 255)

#include <Array.h>
#include <Printable.h>
    template <size_t N_NUM_DIGITOS>
    class EstrategiaPadding : public Printable {
        public:
            virtual void aplicarPadding(Array<byte, N_NUM_DIGITOS> &digitos, Array<byte, N_NUM_DIGITOS> &salida) = 0;
    };
#endif

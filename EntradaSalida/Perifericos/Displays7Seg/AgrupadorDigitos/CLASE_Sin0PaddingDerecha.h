#ifndef SIN_0PADDING_DERECHA
#define SIN_0PADDING_DERECHA

#include "INTERFAZ_EstrategiaPadding.h"
#include "../../../../Utils/FuncionesGlobales.h"
    template <size_t NumDigitos>
    class Sin0PaddingDerecha : public EstrategiaPadding<NumDigitos> {
        public:
            void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) override {
                completar(salida, DISPLAY7SEG_APAGADO, NumDigitos - digitos.size());
                agregarFinal(digitos, salida);
            }
    };
#endif

#ifndef SIN_0PADDING_IZQUIERDA
#define SIN_0PADDING_IZQUIERDA

#include "INTERFAZ_EstrategiaPadding.h"
#include "../../../../Utils/FuncionesGlobales.h"
    template <size_t NumDigitos>
    class Sin0PaddingIzquierda : public EstrategiaPadding<NumDigitos> {
        public:
            void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) override {
                agregarFinal(digitos, salida);
                completar(salida, DISPLAY7SEG_APAGADO);
            }
    };
#endif

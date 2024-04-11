#ifndef SIN_0PADDING_CENTRO
#define SIN_0PADDING_CENTRO

#include "INTERFAZ_EstrategiaPadding.h"
#include "../../../../Utils/FuncionesGlobales.h"
    template <size_t NumDigitos>
    class Sin0PaddingCentro {
        public:
            void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) override {
                completar(salida, DISPLAY7SEG_APAGADO, (NumDigitos - digitos.size()) / 2);
                agregarFinal(digitos, salida);
                completar(salida, DISPLAY7SEG_APAGADO);
            }
    };
#endif

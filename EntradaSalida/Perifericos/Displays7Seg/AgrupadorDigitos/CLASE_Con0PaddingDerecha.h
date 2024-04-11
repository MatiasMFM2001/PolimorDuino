#ifndef CON_0PADDING_DERECHA
#define CON_0PADDING_DERECHA

#include "INTERFAZ_EstrategiaPadding.h"
#include "../../../../Utils/FuncionesGlobales.h"
    template <size_t NumDigitos>
    class Con0PaddingDerecha {
        public:
            void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) override {
                completar(salida, 0, NumDigitos - digitos.size());
                agregarFinal(digitos, salida);
            }
    };
#endif

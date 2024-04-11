#ifndef SIN_0PADDING_IZQUIERDA
#define SIN_0PADDING_IZQUIERDA

#include "INTERFAZ_EstrategiaPadding.h"
    template <size_t NumDigitos>
    class Sin0PaddingIzquierda {
        public:
            void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) override {
                for (byte selec: digitos) {
                    salida.push_back(selec);
                }

                for (size_t cont = digitos.size(), cont < salida.size(), ++cont) {
                    salida.push_back(DISPLAY7SEG_APAGADO);
                }
            }
    };
#endif

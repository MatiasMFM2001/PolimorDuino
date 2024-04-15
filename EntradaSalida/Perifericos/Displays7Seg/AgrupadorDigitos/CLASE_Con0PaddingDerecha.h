#ifndef CON_0PADDING_DERECHA
#define CON_0PADDING_DERECHA

#include "INTERFAZ_EstrategiaPadding.h"
#include "../../../../Utils/FuncionesGlobales.h"
    template <size_t NumDigitos>
    class Con0PaddingDerecha : public EstrategiaPadding<NumDigitos> {
        public:
            void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) override {
                completar(salida, (byte) 0, NumDigitos - digitos.size());
                agregarFinal(digitos, salida);
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "Con0PaddingDerecha");
            }
    };
#endif

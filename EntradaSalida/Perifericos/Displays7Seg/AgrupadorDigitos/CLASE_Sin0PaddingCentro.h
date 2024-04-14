#ifndef SIN_0PADDING_CENTRO
#define SIN_0PADDING_CENTRO

#include "INTERFAZ_EstrategiaPadding.h"
#include "../../../../Utils/FuncionesGlobales.h"
    template <size_t NumDigitos>
    class Sin0PaddingCentro : public EstrategiaPadding<NumDigitos> {
        public:
            void aplicarPadding(Array<byte, NumDigitos> &digitos, Array<byte, NumDigitos> &salida) override {
                completar(salida, DISPLAY7SEG_APAGADO, (NumDigitos - digitos.size()) / 2);
                agregarFinal(digitos, salida);
                completar(salida, DISPLAY7SEG_APAGADO);
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print& impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "Sin0PaddingCentro");
            }
    };
#endif

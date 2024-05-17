/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SIN_0PADDING_CENTRO
#define SIN_0PADDING_CENTRO

#include "INTERFAZ_EstrategiaPadding.h"
#include "../../../../Utils/FuncionesGlobales.h"
    template <size_t N_NUM_DIGITOS>
    class Sin0PaddingCentro : public EstrategiaPadding<N_NUM_DIGITOS> {
        public:
            void aplicarPadding(Array<byte, N_NUM_DIGITOS> &digitos, Array<byte, N_NUM_DIGITOS> &salida) override {
                completar(salida, DISPLAY7SEG_APAGADO, (N_NUM_DIGITOS - digitos.size()) / 2);
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
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "Sin0PaddingCentro");
            }
    };
#endif

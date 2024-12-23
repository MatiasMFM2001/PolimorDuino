/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef LED_WS2812
#define LED_WS2812

#include "CLASE_LedRGBW.h"
#include <Adafruit_NeoPixel.h>
    class LedWS2812 : public LedRGBW {
        private:
            Adafruit_NeoPixel *tiraRGBW;
            size_t indiceTira;

        public:
            LedWS2812(ColorRGBW colorApagado, ColorRGBW colorEncendido, Adafruit_NeoPixel *tiraRGBW, size_t indiceTira, bool estadoInicial = false);
            
            virtual void mostrar() override;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override;
    };
#endif

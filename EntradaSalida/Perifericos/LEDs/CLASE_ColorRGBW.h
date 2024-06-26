/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef COLOR_RGBW
#define COLOR_RGBW

#include <Arduino.h>
#include <Printable.h>
    /**
     * @brief Almacena los brillos de los subpíxeles de un color RGBW.
     */
    class ColorRGBW : public Printable {
        private:
            /** @brief Brillo del subpíxel rojo. */
            byte rojo;
            
            /** @brief Brillo del subpíxel verde. */
            byte verde;
            
            /** @brief Brillo del subpíxel azul. */
            byte azul;
            
            /** @brief Brillo del subpíxel blanco. */
            byte blanco;
        
        public:
            ColorRGBW(byte rojo = 0, byte verde = 0, byte azul = 0, byte blanco = 0);
            
            byte getRojo(void);
            byte getVerde(void);
            byte getAzul(void);
            byte getBlanco(void);
            
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

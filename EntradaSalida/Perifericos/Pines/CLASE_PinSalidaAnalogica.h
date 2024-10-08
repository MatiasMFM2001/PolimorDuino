/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PIN_SALIDA_ANALOGICA
#define PIN_SALIDA_ANALOGICA

#include "CLASE_Pin.h"
    /**
     * @brief Permite encapsular en un objeto, un pin de Salida analógica.
     */
    template <typename T, byte N_NUM_BITS>
    class PinSalidaAnalogica : public Pin<OUTPUT>, public SalidaAnalogica<T, N_NUM_BITS> {
        public:
            /**
             * @brief Construye un PinSalidaAnalogica, con el número de pin y
             *  configuración de inversión especificados.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @c true para invertir el funcionamiento,
             *  @c false para el caso contrario.
             */
            PinSalidaAnalogica(pin_size_t numPin = -1, bool invertir = false)
                : Pin<OUTPUT>(numPin, NUM_ANALOG_INPUTS)
                , SalidaAnalogica<T, N_NUM_BITS>(invertir)
            {}
        
            void escribirBajoNivel(T valor) override {
                if (this -> pinValido) {
                    analogWrite(this -> pin);
                }
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "PinSalidaAnalogica") + SUPERCLASES_A_JSON(impresora, Pin<OUTPUT>, (SalidaAnalogica<T, N_NUM_BITS>));
            }
    };
#endif

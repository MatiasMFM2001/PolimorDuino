/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PIN_ENTRADA_ANALOGICA
#define PIN_ENTRADA_ANALOGICA

#include "CLASE_Pin.h"
#include "../../Entradas/CLASE_EntradaAnalogica.h"
    /**
     * @brief Permite encapsular en un objeto, un pin de Entrada analógica.
     */
    template <typename T, byte N_NUM_BITS>
    class PinEntradaAnalogica : public Pin<INPUT>, public EntradaAnalogica<T, N_NUM_BITS> {
        public:
            /**
             * @brief Construye un PinEntradaAnalogica, con el número de pin,
             *  configuración de inversión y estado inicial especificados.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @c true para invertir el funcionamiento,
             *  @c false para el caso contrario.
             */
            PinEntradaAnalogica(pin_size_t numPin = -1, bool invertir = false)
                : Pin(numPin, NUM_ANALOG_INPUTS)
                , EntradaAnalogica<T, N_NUM_BITS>(invertir)
            {}
        
            /**
             * @returns El valor leído del pin, sin invertir.
             */
            T leerBajoNivel(void) override {
                return (this -> pinValido) * analogRead(this -> numPin);
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "PinEntradaAnalogica") + SUPERCLASES_A_JSON(impresora, Pin, (EntradaAnalogica<T, N_NUM_BITS>));
            }
    };
#endif

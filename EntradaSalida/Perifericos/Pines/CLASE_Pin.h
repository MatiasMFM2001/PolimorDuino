#ifndef PIN
#define PIN

#include <Arduino.h>
#include <Printable.h>
#include "../../../Utils/FuncionesGlobales.h"
#include "../../../Utils/INTERFAZ_Inicializable.h"
#include "../../../Logger/FuncionesJSON.h"

#if !(defined(ARDUINO_ARCH_RP2040) && !defined(__MBED__))
    typedef byte pin_size_t;
#endif
    /**
     * @brief Permite encapsular en un objeto, un pin de Entrada/Salida.
     */
    template <byte MODO_PIN>
    class Pin : virtual public Printable, public Inicializable {
        protected:
            /** @brief El número identificatorio del pin en la placa. */
            pin_size_t numPin;

            /** @brief Si el número de pin es válido o no. */
            bool pinValido;
        
        public:
            /**
             * @brief Construye un Pin, con el número de pin, configuración de
             *  inversión y modo especificados. Además, verifica si el pin es
             *  válido, guardando el resultado.
             * 
             * @param numPin El número de pin especificado.
             * @param MODO_PIN El número constante que establece cómo configurar
             *  el pin.
             * @param totalPines La cantidad total de pines de este tipo en la
             *  placa.
             */
            Pin(pin_size_t numPin, pin_size_t totalPines)
                : numPin(numPin), pinValido(enRango<pin_size_t>(numPin, 0, totalPines - 1)
        #if (defined(ARDUINO_ARCH_RP2040) && !defined(__MBED__))
                || enRango<pin_size_t>(numPin, 32, 34)
        #endif
                )
            {}

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             * 
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "Pin", MODO_PIN, numPin, pinValido);
            }

            void inicializar(void) override {
                if (this -> pinValido) {
                    pinMode(numPin, MODO_PIN);
                }
            }
    };
#endif

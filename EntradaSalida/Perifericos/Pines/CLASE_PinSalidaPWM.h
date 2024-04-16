#ifndef PIN_SALIDA_PWM
#define PIN_SALIDA_PWM

#include "CLASE_Pin.h"
#include "../../Salidas/CLASE_SalidaPWM.h"
    /**
     * @brief Permite encapsular en un objeto, un pin de Salida PWM.
     */
    template <typename T, byte N_NUM_BITS>
    class PinSalidaPWM : public Pin, public SalidaPWM<T, N_NUM_BITS> {
        public:
            /**
             * @brief Construye un PinSalidaPWM, con el número de pin y
             *  configuración de inversión especificados.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @c true para invertir el funcionamiento,
             *  @c false para el caso contrario.
             */
            PinSalidaPWM(byte numPin = -1, bool invertir = false)
                : Pin(numPin, OUTPUT, NUM_DIGITAL_PINS)
                , SalidaPWM<T, N_NUM_BITS>(invertir)
            {}
        
            void escribirBajoNivel(T valor) override {
                if (this -> pinValido) {
                    analogWrite(this -> numPin, valor);
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
                return OBJETO_A_JSON(impresora, "PinSalidaPWM") + SUPERCLASES_A_JSON(impresora, Pin, (SalidaPWM<T, N_NUM_BITS>));
            }
    };
#endif

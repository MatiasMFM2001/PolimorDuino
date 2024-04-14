#ifndef PIN_SALIDA_PWM
#define PIN_SALIDA_PWM

#include "CLASE_Pin.h"
#include "../../Salidas/CLASE_SalidaPWM.h"
	/**
	 * @brief Permite encapsular en un objeto, un pin de Salida PWM.
	 */
    template <typename T, byte NumBits>
    class PinSalidaPWM : public Pin, public SalidaPWM<T, NumBits> {
        public:
			/**
             * @brief Construye un PinSalidaPWM, con el número de pin y
             *  configuración de inversión especificados.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @code true para invertir el funcionamiento,
             *  @code false para el caso contrario.
             */
            PinSalidaPWM(byte numPin = -1, bool invertir = false)
                : Pin(numPin, OUTPUT, NUM_DIGITAL_PINS)
                , SalidaPWM<T, NumBits>(invertir)
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
            virtual size_t printTo(Print& impresora) const override {
                return OBJETO_A_JSON(impresora, "PinSalidaPWM", T, NumBits) + SUPERCLASES_A_JSON(impresora, Pin, SalidaPWM<T, NumBits>);
            }
    };
#endif

#ifndef PIN_SALIDA_PWM
#define PIN_SALIDA_PWM

#include "CLASE_Pin.h"
#include <PinChangeInterrupt.h>
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
            PinSalidaPWM(byte numPin = -1, bool invertir = false);
        
            void escribirBajoNivel(T valor) override {
                if (this -> pinValido) {
                    analogWrite(this -> pin);
                }
            }
    };
#endif

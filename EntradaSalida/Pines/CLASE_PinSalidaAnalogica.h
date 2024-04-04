#ifndef PIN_SALIDA_ANALOGICA
#define PIN_SALIDA_ANALOGICA

#include "CLASE_Pin.h"
#include <PinChangeInterrupt.h>
	/**
	 * @brief Permite encapsular en un objeto, un pin de Salida analógica.
	 */
    template <typename T, byte NumBits>
    class PinSalidaAnalogica : public Pin, public SalidaAnalogica<T, NumBits> {
        public:
			/**
             * @brief Construye un PinSalidaAnalogica, con el número de pin,
             *  configuración de inversión y estado inicial especificados.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @code true para invertir el funcionamiento,
             *  @code false para el caso contrario.
             */
            PinSalidaAnalogica(byte numPin = -1, bool invertir = false);
        
            void escribirBajoNivel(T valor) override {
                if (this -> pinValido) {
                    analogWrite(this -> pin);
                }
            }
    };
#endif

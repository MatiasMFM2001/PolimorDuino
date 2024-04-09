#ifndef PIN_ENTRADA_ANALOGICA
#define PIN_ENTRADA_ANALOGICA

#include "CLASE_Pin.h"
#include "../../Entradas/CLASE_EntradaAnalogica.h"
	/**
	 * @brief Permite encapsular en un objeto, un pin de Entrada analógica.
	 */
    template <typename T, byte NumBits>
    class PinEntradaAnalogica : public Pin, public EntradaAnalogica<T, NumBits> {
        public:
			/**
             * @brief Construye un PinEntradaAnalogica, con el número de pin,
             *  configuración de inversión y estado inicial especificados.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @code true para invertir el funcionamiento,
             *  @code false para el caso contrario.
             */
            PinEntradaAnalogica(byte numPin = -1, bool invertir = false);
        
			/**
			 * @returns El valor leído del pin, sin invertir.
			 */
            T leerBajoNivel(void) override {
                return (this -> pinValido) * analogRead(this -> pin);
            }
    };
#endif

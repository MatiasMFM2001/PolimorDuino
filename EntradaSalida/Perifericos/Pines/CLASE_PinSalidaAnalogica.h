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
             * @brief Construye un PinSalidaAnalogica, con el número de pin y
             *  configuración de inversión especificados.
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

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print& impresora) const override {
                return OBJETO_A_JSON(impresora, "PinSalidaAnalogica", T, NumBits) + SUPERCLASES_A_JSON(impresora, Pin, SalidaAnalogica<T, NumBits>);
            }
    };
#endif

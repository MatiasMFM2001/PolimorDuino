#ifndef PIN
#define PIN

#include <Arduino.h>
	/**
	 * @brief Permite encapsular en un objeto, un pin de E/S.
	 */
    class Pin : virtual public Printable {
        protected:
			/** @brief El número identificatorio del pin en la placa. */
            byte numPin;
            
            /** @brief Si invertir el funcionamiento del pin o no. */
            bool invertir;
            
            /** @brief Si el número de pin es válido o no. */
            bool pinValido;
        
        public:
			/**
             * @brief Construye un Pin, con el número de pin, configuración de
             *  inversión y modo especificados. Además, verifica si el pin es
             *  válido, guardando el resultado.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @code true para invertir el funcionamiento,
             *  @code false para el caso contrario.
             * @param modoPin El número constante que establece cómo configurar
             *  el pin.
             */
            Pin(byte numPin, bool invertir, byte modoPin);
        
			/**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             * 
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print& impresora) const override;
    };
#endif

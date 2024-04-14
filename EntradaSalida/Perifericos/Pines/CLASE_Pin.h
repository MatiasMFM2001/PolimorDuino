#ifndef PIN
#define PIN

#include <Arduino.h>
#include <Printable.h>
    /**
     * @brief Permite encapsular en un objeto, un pin de Entrada/Salida.
     */
    class Pin : virtual public Printable {
        protected:
            /** @brief El número identificatorio del pin en la placa. */
            byte numPin;

            /** @brief Si el número de pin es válido o no. */
            bool pinValido;
        
        public:
            /**
             * @brief Construye un Pin, con el número de pin, configuración de
             *  inversión y modo especificados. Además, verifica si el pin es
             *  válido, guardando el resultado.
             * 
             * @param numPin El número de pin especificado.
             * @param modoPin El número constante que establece cómo configurar
             *  el pin.
             * @param totalPines La cantidad total de pines de este tipo en la
             *  placa.
             */
            Pin(byte numPin, byte modoPin, byte totalPines);
        
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

#ifndef PIN_SALIDA_DIGITAL
#define PIN_SALIDA_DIGITAL

#include "CLASE_Pin.h"
#include "INTERFAZ_Pulsable.h"
	/**
	 * @brief Permite encapsular en un objeto, un pin de Salida digital. Además,
	 *  implementa la interfaz @code Pulsable.
	 */
    class PinSalidaDigital : public Pin, public SalidaDigital {
        public:
			/**
             * @brief Construye un PinSalida, con el número de pin,
             *  configuración de inversión y estado inicial especificados.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @code true para invertir el funcionamiento,
             *  @code false para el caso contrario.
             * @param estadoInicial @code true para iniciar el programa con
             *  el pin encendido, @code false para el caso contrario.
             */
            PinSalidaDigital(byte numPin = -1, bool invertir = false, bool estadoInicial = false);
        
			/**
             * @brief Establece el valor actual del pin al especificado.
             * 
             * @param valor @code true para encenderlo, @code false para el caso
             *  contrario.
             */
            void escribirBajoNivel(bool valor) override;
    };
#endif
#ifndef PIN_SALIDA
#define PIN_SALIDA

#include "CLASE_Pin.h"
#include "INTERFAZ_Pulsable.h"
	/**
	 * @brief Permite encapsular en un objeto, un pin de Salida digital. Además,
	 *  implementa la interfaz @code Pulsable.
	 */
    class PinSalida : public Pin, public Pulsable {
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
            PinSalida(byte numPin = -1, bool invertir = false, bool estadoInicial = false);
        
			/**
             * @brief Establece el estado actual del pin al especificado.
             * 
             * @param valor @code true para encenderlo, @code false para el caso
             *  contrario.
             */
            void setEstado(bool valor) override;
    };
#endif

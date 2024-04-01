#ifndef PIN_ENTRADA
#define PIN_ENTRADA

#include "CLASE_Pin.h"
#include <PinChangeInterrupt.h>
	/**
	 * @brief Permite encapsular en un objeto, un pin de Entrada digital. Además,
	 *  simplifica el uso de la librería de interrupciones por flanco.
	 */
    class PinEntrada : public Pin {
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
            PinEntrada(byte numPin = -1, bool invertir = false, bool habilitarPullUp = false);
        
			/**
			 * @returns El valor leído del pin, invertido o no según lo
			 *  configurado.
			 */
            bool leer();
        
			/**
			 * @returns El número identificatorio de interrupción por flancos,
			 *  según el número de pin.
			 */
            byte getNumPCINT();
            
            /**
             * @brief Establece la función que será ejecutada cuando se detecte
             *  un flanco del tipo especificado (independientemente de la
             *  configuración de inversión).
             * 
             * @param funcion La función callback a ser ejecutada.
             * @param modo El modo de detección de flancos.
             */
            void vincularFuncionPCINT(callback funcion, byte modo);
            
            /**
             * @brief Desvincula la función establecida previamente, con las
             *  interrupciones por flanco emitidas por este pin.
             */
            void desvincularFuncionPCINT();
            
            /**
             * @brief Permite que este pin emita interrupciones por flanco.
             */
            void habilitarInterrupcion();
            
            /**
             * @brief Deniega que este pin emita interrupciones por flanco.
             */
            void deshabilitarInterrupcion();
    };
#endif

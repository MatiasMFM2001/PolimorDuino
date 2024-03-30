#ifndef PIN_ENTRADA
#define PIN_ENTRADA

#include "CLASE_Pin.h"
#include <PinChangeInterrupt.h>
    class PinEntrada : public Pin {
        public:
            PinEntrada(byte numPin = -1, bool invertir = false, bool habilitarPullUp = false);
        
            bool leer();
        
            byte getNumPCINT();
            void vincularFuncionPCINT(callback funcion, byte modo);
            void desvincularFuncionPCINT();
            void habilitarInterrupcion();
            void deshabilitarInterrupcion();
    };
#endif

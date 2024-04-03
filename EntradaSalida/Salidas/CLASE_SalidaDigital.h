#ifndef SALIDA_CONTINUA
#define SALIDA_CONTINUA

#include "CLASE_Salida.h"
    class SalidaDigital : Salida<bool, 1> {    
        public:
            SalidaDigital(bool invertir);
    };
#endif

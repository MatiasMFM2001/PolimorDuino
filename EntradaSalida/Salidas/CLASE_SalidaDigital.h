#ifndef SALIDA_CONTINUA
#define SALIDA_CONTINUA

#include "CLASE_Salida.h"
    class SalidaDigital : Salida<bool, 1>, Pulsable {    
        public:
            SalidaDigital(bool invertir, bool estadoInicial);
            
            void setEstado(bool valor) override;
    };
#endif

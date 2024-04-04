#ifndef SALIDA_DIGITAL
#define SALIDA_DIGITAL

#include "CLASE_Salida.h"
    class SalidaDigital : Salida<bool, 1>, Pulsable {    
        public:
            SalidaDigital(bool invertir, bool estadoInicial);
            
            void setEstado(bool valor) override;
    };
#endif

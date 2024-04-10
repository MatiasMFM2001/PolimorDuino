#ifndef SALIDA_DIGITAL
#define SALIDA_DIGITAL

#include "CLASE_Salida.h"
#include "../../Utils/CLASE_Pulsable.h"
    class SalidaDigital : public Salida<bool, 1>, public Pulsable {
        public:
            SalidaDigital(bool invertir, bool estadoInicial);
            
            void setEstado(bool valor) override;
    };
#endif

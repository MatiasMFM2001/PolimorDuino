#ifndef SALIDA_DIGITAL
#define SALIDA_DIGITAL

#include "CLASE_Salida.h"
#include "../../Utils/CLASE_Pulsable.h"
#include "../TIPOS_EnterosAnalogicos.h"
    class SalidaDigital : public Salida<BOOL_1_BIT>, public Pulsable {
        public:
            SalidaDigital(bool invertir, bool estadoInicial);
            
            void setEstado(bool valor) override;
    };
#endif

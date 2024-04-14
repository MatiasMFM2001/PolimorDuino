#ifndef ENTRADA_DIGITAL
#define ENTRADA_DIGITAL

#include "CLASE_Entrada.h"
#include "../TIPOS_EnterosAnalogicos.h"
    class EntradaDigital : public Entrada<BOOL_1_BIT> {
        public:
            EntradaDigital(bool invertir);
    };
#endif

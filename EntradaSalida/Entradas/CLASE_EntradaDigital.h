#ifndef ENTRADA_DIGITAL
#define ENTRADA_DIGITAL

#include "CLASE_Entrada.h"
    class EntradaDigital : Entrada<bool, 1> {
        public:
            EntradaDigital(bool invertir);
    };
#endif

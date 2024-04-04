#ifndef ENTRADA_DIGITAL
#define ENTRADA_DIGITAL

#include "CLASE_Entrada.h"
    class EntradaDigital : public Entrada<bool, 1> {
        public:
            EntradaDigital(bool invertir);
    };
#endif

#ifndef INVERSOR_PULSABLE
#define INVERSOR_PULSABLE

#include "CLASE_Pulsable.h"
    class InversorPulsable : public Pulsable {
        private:
            Pulsable *decorado;

        public:
            InversorPulsable(bool invertir, Pulsable *decorado);

            void encender(void) override;
            void apagar(void) override;
    };
#endif

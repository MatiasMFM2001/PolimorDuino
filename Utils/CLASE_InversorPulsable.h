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

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print& impresora) const override;
    };
#endif

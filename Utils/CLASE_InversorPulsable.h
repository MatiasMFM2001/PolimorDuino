#ifndef INVERSOR_PULSABLE
#define INVERSOR_PULSABLE
    class InversorPulsable : public Pulsable {
        private:
            Pulsable *decorado;

        public:
            InversorPulsable(Pulsable *decorado);

            void encender(void) override;
            void apagar(void) override;
    };
#endif

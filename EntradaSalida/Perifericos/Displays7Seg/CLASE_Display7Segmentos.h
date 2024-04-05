#ifndef DISPLAY_7_SEGMENTOS 
#define DISPLAY_7_SEGMENTOS
    class Display7Segmentos : public Pulsable {
        public:
            Display7Segmentos(byte numeroInicial, bool estadoInicial);
            
            virtual void setNumero(byte valor) = 0;
    };
#endif

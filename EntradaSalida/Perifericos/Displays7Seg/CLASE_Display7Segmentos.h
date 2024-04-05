#ifndef DISPLAY_7_SEGMENTOS 
#define DISPLAY_7_SEGMENTOS
    template <typename T>
    class Display7Segmentos : public Pulsable {
        public:
            Display7Segmentos(T numeroInicial, bool estadoInicial)
                , numeroInicial(numeroInicial)
            {
                this -> setNumero(numeroInicial);
                Pulsable::Pulsable(estadoInicial);
            }
            
            virtual void setNumero(T valor) = 0;
    };
#endif

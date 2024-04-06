#ifndef AGRUPADOR_DIGITOS
#define AGRUPADOR_DIGITOS
    template <typename T, size_t NumDigitos>
    class AgrupadorDigitos : Display7Segmentos<T> {
        private:
            Array<Display7Segmentos<byte>*, NumDigitos> digitos; // Orden: Menos significativo a más significativo
        
        public:
            AgrupadorDigitos(T numeroInicial, bool estadoInicial, Array<Display7Segmentos<byte>*, NumDigitos> digitos)
                : digitos(digitos)
            {
                Display7Segmentos::Display7Segmentos(numeroInicial, estadoInicial);
            }
            
            void setNumero(T valor, byte base = DEC) override {
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    selec -> setNumero(valor % base);
                    valor /= base;
                }
            }
            
            void setEstado(bool valor) override {
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    selec -> setEstado(valor);
                }
            }
    }
#endif

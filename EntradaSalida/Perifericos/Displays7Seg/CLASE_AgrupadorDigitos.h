#ifndef AGRUPADOR_DIGITOS
#define AGRUPADOR_DIGITOS
    template <typename T, size_t NumDigitos>
    class AgrupadorDigitos : Display7Segmentos<T> {
        private:
            Array<Display7Segmentos<byte>*, NumDigitos> digitos; // Orden: Menos significativo a más significativo
            byte baseNumerica;
        
        public:
            AgrupadorDigitos(T numeroInicial, bool estadoInicial, Array<Display7Segmentos<byte>*, NumDigitos> digitos, byte baseNumerica)
                : digitos(digitos), baseNumerica(baseNumerica)
            {
                Display7Segmentos::Display7Segmentos(numeroInicial, estadoInicial);
            }
            
            void setNumero(T valor) override {
                byte base = this -> baseNumerica;
                
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

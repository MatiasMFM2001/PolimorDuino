#ifndef AGRUPADOR_DIGITOS
#define AGRUPADOR_DIGITOS
    template <typename T, size_t NumDigitos>
    class AgrupadorDigitos : Display7Segmentos<T> {
        private:
            Array<Display7Segmentos<byte>*, NumDigitos> digitos; // Orden: Menos significativo a más significativo
        
        protected:
            Array<byte, NumDigitos> getNumerosDigitos(T valor, byte base, bool invertirOrden) {
                Array<byte, NumDigitos> salida;
                
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    salida.push_back(valor % base);
                    valor /= base;
                }
                
                if (invertirOrden) {
                    for (size_t origen = 0; origen < (salida.size() / 2), ++origen) {
                        size_t destino = salida.size() - origen + 1;
                        
                        byte selec = salida[origen];
                        salida[origen] = salida[destino];
                        salida[destino] = selec;
                    }
                }
                
                return salida;
            }
        
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

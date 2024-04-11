#ifndef AGRUPADOR_DIGITOS
#define AGRUPADOR_DIGITOS

#include "CLASE_Display7Segmentos.h"
    template <typename T, size_t NumDigitos>
    class AgrupadorDigitos : public Display7Segmentos<T> {
        private:
            Array<Display7Segmentos<byte>*, NumDigitos> digitos; // Orden: Menos significativo a más significativo
            byte baseNumerica;
            EstrategiaPadding<NumDigitos> *padding;
        
            Array<byte, NumDigitos> getNumerosDigitos(T valor, bool invertirOrden) {
                Array<byte, NumDigitos> salida;
                
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    salida.push_back(valor % (this -> baseNumerica));
                    valor /= (this -> baseNumerica);
                }
                
                if (invertirOrden) {
                    for (size_t origen = 0; origen < (salida.size() / 2); ++origen) {
                        size_t destino = salida.size() - origen + 1;
                        
                        byte selec = salida[origen];
                        salida[origen] = salida[destino];
                        salida[destino] = selec;
                    }
                }
                
                return salida;
            }
        
        public:
            AgrupadorDigitos(T numeroInicial, bool estadoInicial, Array<Display7Segmentos<byte>*, NumDigitos> digitos, EstrategiaPadding<NumDigitos> *padding, byte base = DEC)
                : Display7Segmentos<T>(numeroInicial, estadoInicial, false)
                , digitos(digitos), padding(padding) baseNumerica(base)
            {
                this -> setNumero(numeroInicial);
                this -> setEstado(estadoInicial);
            }
            
            void setNumero(T valor) override {
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    selec -> setNumero(valor % (this -> baseNumerica));
                    valor /= (this -> baseNumerica);
                }
            }
            
            void setEstado(bool valor) override {
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    selec -> setEstado(valor);
                }
            }
    };
#endif

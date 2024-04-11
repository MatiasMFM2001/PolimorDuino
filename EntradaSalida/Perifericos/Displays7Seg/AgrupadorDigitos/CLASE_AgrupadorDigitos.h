#ifndef AGRUPADOR_DIGITOS
#define AGRUPADOR_DIGITOS

#define DISPLAY7SEG_APAGADO 16
#include "CLASE_Display7Segmentos.h"
#include "../../../../Utils/FuncionesGlobales.h"
    template <typename T, size_t NumDigitos>
    class AgrupadorDigitos : public Display7Segmentos<T> {
        private:
            Array<Display7Segmentos<byte>*, NumDigitos> digitos; // Orden: Menos significativo a más significativo
            byte baseNumerica;
            EstrategiaPadding<NumDigitos> *padding;
        
            Array<byte, NumDigitos> getNumerosDigitos(T valor) {
                Array<byte, NumDigitos> salida;
                
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    salida.push_back(valor % (this -> baseNumerica));
                    valor /= (this -> baseNumerica);
                }
                
                invertirOrden(salida);
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
                Array<byte, NumDigitos> digitos = this -> getNumerosDigitos(valor);
                
                Array<byte, NumDigitos> procesados;
                this -> padding -> aplicarPadding(digitos, procesados);
                
                for (size_t cont = 0; cont < procesados.len(); ++cont) {
                    Display7Segmentos<byte>* digSelec = this -> digitos[cont];
                    byte numSelec = procesados[cont];
                    
                    if (numSelec != DISPLAY7SEG_APAGADO) {
                        digSelec -> setNumero(numSelec);
                        digSelec -> encender();
                    }
                    else {
                        digSelec -> apagar();
                    }
                }
            }
            
            void setEstado(bool valor) override {
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    selec -> setEstado(valor);
                }
            }
    };
#endif

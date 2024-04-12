#ifndef AGRUPADOR_DIGITOS
#define AGRUPADOR_DIGITOS

#include "../CLASE_Display7Segmentos.h"
#include "../../../../Utils/FuncionesGlobales.h"
#include "INTERFAZ_EstrategiaPadding.h"
    template <typename T, size_t NumDigitos>
    class AgrupadorDigitos : public Display7Segmentos<T> {
        private:
            Array<Display7Segmentos<byte>*, NumDigitos> digitos; // Orden: Menos significativo a más significativo
            byte baseNumerica;
            EstrategiaPadding<NumDigitos> *padding;
        
            Array<byte, NumDigitos> getNumerosDigitos(T valor) {
                Array<byte, NumDigitos> salida;
                
                if (valor == 0) {
                    salida.push_back(0);
                    return salida;
                }
                
                while ((valor > 0) && !salida.full()) {
                    salida.push_back(valor % (this -> baseNumerica));
                    valor /= (this -> baseNumerica);
                }
                
                invertirOrden(salida);
                return salida;
            }
        
        public:
            AgrupadorDigitos(T numeroInicial, bool estadoInicial, Array<Display7Segmentos<byte>*, NumDigitos> digitos, EstrategiaPadding<NumDigitos> *padding, byte base = DEC)
                : Display7Segmentos<T>(numeroInicial, estadoInicial, false)
                , digitos(digitos), padding(padding), baseNumerica(base)
            {
                this -> setNumero(numeroInicial);
                this -> setEstado(estadoInicial);
            }
            
            void setNumero(T valor) override {
                Array<byte, NumDigitos> digitos = this -> getNumerosDigitos(valor);
                
                Array<byte, NumDigitos> procesados;
                this -> padding -> aplicarPadding(digitos, procesados);
                
                for (size_t cont = 0; cont < procesados.size(); ++cont) {
                    Display7Segmentos<byte>* digSelec = this -> digitos[cont];
                    byte numSelec = procesados[cont];
                    
                    digSelec -> setNumero(numSelec);
                    digSelec -> setEstado(numSelec != DISPLAY7SEG_APAGADO);
                }
            }
            
            void setEstado(bool valor) override {
                for (Display7Segmentos<byte> *selec: this -> digitos) {
                    selec -> setEstado(valor);
                }
            }
    };
#endif

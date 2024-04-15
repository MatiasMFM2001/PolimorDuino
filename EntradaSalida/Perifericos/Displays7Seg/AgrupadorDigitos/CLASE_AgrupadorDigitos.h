#ifndef AGRUPADOR_DIGITOS
#define AGRUPADOR_DIGITOS

#include "../CLASE_Display7Segmentos.h"
#include "../../../../Utils/FuncionesGlobales.h"
#include "INTERFAZ_EstrategiaPadding.h"
    template <typename T, size_t N_NUM_DIGITOS>
    class AgrupadorDigitos : public Display7Segmentos<T> {
        private:
            Array<Display7Segmentos<byte>*, N_NUM_DIGITOS> digitos; // Orden: Menos significativo a más significativo
            byte baseNumerica;
            EstrategiaPadding<N_NUM_DIGITOS> *padding;
        
            Array<byte, N_NUM_DIGITOS> getNumerosDigitos(T valor) {
                Array<byte, N_NUM_DIGITOS> salida;
                
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
            AgrupadorDigitos(T numeroInicial, bool estadoInicial, Array<Display7Segmentos<byte>*, N_NUM_DIGITOS> digitos, EstrategiaPadding<N_NUM_DIGITOS> *padding, byte base = DEC)
                : Display7Segmentos<T>(numeroInicial, estadoInicial, false)
                , digitos(digitos), baseNumerica(base), padding(padding)
            {
                this -> setNumero(numeroInicial);
                this -> setEstado(estadoInicial);
            }
            
            void setNumero(T valor) override {
                Array<byte, N_NUM_DIGITOS> digitos = this -> getNumerosDigitos(valor);
                
                Array<byte, N_NUM_DIGITOS> procesados;
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

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "AgrupadorDigitos", digitos, baseNumerica, padding) + SUPERCLASES_A_JSON(impresora, Display7Segmentos<T>);
            }
    };
#endif

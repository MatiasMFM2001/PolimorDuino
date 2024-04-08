#ifndef DISPLAY_7_SEGMENTOS_PARALELO
#define DISPLAY_7_SEGMENTOS_PARALELO

#include <Array.h>
#include "CLASE_Display7Segmentos.h"
    template <size_t NumSalidasDatos>
    class Display7SegmentosParalelo : public Display7Segmentos<byte> {
        private:
            Array<SalidaDigital*, NumSalidasDatos> salidasDatos;
            SalidaDigital *salidaEnable;
        
        protected:
            virtual byte getBits(byte valor) = 0;
        
        public:
            Display7SegmentosParalelo(byte numeroInicial, bool estadoInicial, Array<SalidaDigital*, NumSalidasDatos> salidasDatos, SalidaDigital *salidaEnable)
                : Display7Segmentos(numeroInicial, estadoInicial)
                , salidasDatos(salidasDatos), salidaEnable(salidaEnable)
            {}
        
            void setNumero(byte valor) override {
                LOG("INICIO Display7SegmentosParalelo::setNumero(%d)", valor);
                    byte bits = this -> getBits(valor);
                    
                    for (SalidaDigital *selec: this -> salidasDatos) {
                        selec -> setEstado(bits & 0b00000001);
                        bits >>= 1;
                    }
                LOG("FIN Display7SegmentosParalelo::setNumero(%#x)", valor);
            }
            
            void setEstado(bool valor) override {
                this -> salidaEnable -> setEstado(valor);
            }
        
            size_t printTo(Print& impresora) const override {
                return (imprimirCabeceraJSON(impresora, F("Display7SegmentosParalelo"))
                    + imprimirVariableJSON(impresora, F("salidasDatos"), this -> salidasDatos) + impresora.print(JSON_SEPARADOR)
                    + imprimirVariableJSON(impresora, F("salidaEnable"), this -> salidaEnable) + impresora.print(JSON_CLAUSURA_OBJETO)
                );
            }
    };
#endif
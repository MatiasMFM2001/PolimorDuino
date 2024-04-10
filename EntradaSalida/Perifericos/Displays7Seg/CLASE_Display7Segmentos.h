#ifndef DISPLAY_7_SEGMENTOS 
#define DISPLAY_7_SEGMENTOS

#include "../../../Utils/CLASE_Pulsable.h"
#include <log4arduino.h>
    template <typename T>
    class Display7Segmentos : public Pulsable {
        public:
            Display7Segmentos(T numeroInicial, bool estadoInicial, bool settearNumero = true)
                : Pulsable(estadoInicial, false)
            {
                if (settearNumero) {
                    this -> setNumero(numeroInicial);
                    this -> setEstado(estadoInicial);
                }
            }
            
            virtual void setNumero(T valor) {
                LOG("Display7Segmentos::setNumero(%d) - METODO NO IMPLEMENTADO EN SUBCLASE", valor);
            }
            
            size_t printTo(Print& p) const override {
               return 0;
            }
    };
#endif

#ifndef DISPLAY_7_SEGMENTOS 
#define DISPLAY_7_SEGMENTOS

#include "../../../Utils/CLASE_Pulsable.h"
#include "../../../Inclusiones/InclusionLog4Arduino.h"
#include "../../../Logger/FuncionesJSON.h"
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
    };
#endif

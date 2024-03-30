#ifndef PIN_SALIDA
#define PIN_SALIDA

#include "CLASE_Pin.h"
#include "INTERFAZ_Pulsable.h"
    class PinSalida : public Pin, public Pulsable {
        public:
            PinSalida(byte pin = -1, bool invertir = false, bool estadoInicial = false);
        
            void setEstado(bool valor);
            void encender() override;
            void apagar() override;
        
            size_t printTo(Print& impresora) const override;
    };
#endif
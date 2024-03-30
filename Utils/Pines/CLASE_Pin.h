#ifndef PIN
#define PIN

#include <Arduino.h>
    class Pin : virtual public Printable {
        protected:
            byte numPin;
            bool invertir, pinValido;
        
        public:
            Pin(byte numPin, bool invertir, byte modoPin);
        
            size_t printTo(Print& impresora) const override;
    };
#endif
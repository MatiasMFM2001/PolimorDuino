#ifndef PULSABLE
#define PULSABLE

#include <Printable.h>
    class Pulsable : virtual public Printable {
        public:
            virtual void encender() = 0;
            virtual void apagar() = 0;
    };
#endif
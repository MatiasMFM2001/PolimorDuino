#ifndef MEDIDOR
#define MEDIDOR

#include "InclusionLog4Arduino.h"
    template <typename T>

    class Medidor {
        protected:
            void ejecutarCallback(T ingr) {
                FLOGS("MEDIDOR - Ejecutando ejecutarCallback()");
                LOGS(ingr);
                this -> Callback(ingr);
            }
        
        public:
            virtual void Callback(T valor) {
                FLOGS("MEDIDOR - Ejecutando Callback()");
                LOGS(valor);
            }
    };
#endif

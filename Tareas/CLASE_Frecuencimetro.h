#ifndef FRECUENCIMETRO
#define FRECUENCIMETRO

#include "InclusionTaskSchedulerDeclarations.h"
#include "CLASE_Contador.h"
    class Frecuencimetro : public Task {
        private:
            Contador<unsigned short> contFrec;
            unsigned short ultFrec;
    
        public:
            Frecuencimetro(Scheduler* planif);
    
            bool Callback() override;
            
            void reiniciar();
            void incrementar();
            
            unsigned short getHz();
            bool estaEnCero();
    };
#endif

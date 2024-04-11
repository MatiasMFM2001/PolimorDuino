#ifndef INICIADOR_FINITO
#define INICIADOR_FINITO

#include "CLASE_IniciadorTareas.h"
    class IniciadorFinito : public IniciadorTareas {
        private:
            Contador<size_t> contIteraciones;
        
        public:
            IniciadorFinito(unsigned long msEntreIniciaciones, unsigned long numIniciaciones, Scheduler* planif, Task *tarea);
            
            bool OnEnable(void) override;
            bool deboFinalizar(void) override;
    };
#endif

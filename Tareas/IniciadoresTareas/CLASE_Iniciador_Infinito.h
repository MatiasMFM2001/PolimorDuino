#ifndef INICIADOR_INFINITO
#define INICIADOR_INFINITO

#include "CLASE_IniciadorTareas.h"
    class IniciadorInfinito : public IniciadorTareas {
        public:
            IniciadorInfinito(unsigned long msEntreIniciaciones, Scheduler* planif, Task *tarea);
            
            bool deboFinalizar(void) override;
    };
#endif

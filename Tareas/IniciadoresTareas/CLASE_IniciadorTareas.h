#ifndef INICIADOR_TAREAS
#define INICIADOR_TAREAS

#include "../../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include <Printable.h>
    class IniciadorTareas : public Task, public Printable {
        private:
            Task *tarea;
        
        public:
            IniciadorTareas(unsigned long msEntreIniciaciones, Scheduler *planif, Task *tarea);

            bool Callback(void) override;
            virtual bool deboFinalizar(void) = 0;
    };
#endif

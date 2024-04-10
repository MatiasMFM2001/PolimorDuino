#ifndef INICIADOR_TAREAS
#define INICIADOR_TAREAS

#define _TASK_OO_CALLBACKS
#include <TaskScheduler.h>

#include "../Utils/CLASE_Contador.h"
    class IniciadorTareas : public Task {
        private:
            Task *tarea;
        
        public:
            IniciadorTareas(unsigned long msEntreIniciaciones, unsigned long numIniciacionesInterno, Scheduler *planif, Task *tarea);

            bool Callback(void) override;
            virtual bool deboFinalizar(void) = 0;
    };
#endif

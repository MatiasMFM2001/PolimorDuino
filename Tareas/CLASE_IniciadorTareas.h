#ifndef INICIADOR_TAREAS
#define INICIADOR_TAREAS

#define _TASK_OO_CALLBACKS
#include <TaskScheduler.h>

#include "../Utils/CLASE_Contador.h"
    class IniciadorTareas : public Task {
        private:
            Task *tarea;
            Contador<size_t> contIteraciones;
        
        public:
            IniciadorTareas(unsigned long msEntreIniciaciones, unsigned long numIniciaciones, Scheduler* planif);
            
            bool OnEnable(void) override;
            bool Callback(void) override;
    };
#endif

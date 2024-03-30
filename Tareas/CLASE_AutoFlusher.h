#ifndef CLASE_AUTO_FLUSHER
#define CLASE_AUTO_FLUSHER

#include "InclusionTaskSchedulerDeclarations.h"
#include <Print.h>
    class AutoFlusher : public Task {
        private:
            Print* impresora;
        
        public:
            AutoFlusher(Print* impresora, long msEntreLlamados, Scheduler* planif);
        
            bool Callback() override;
    };
#endif

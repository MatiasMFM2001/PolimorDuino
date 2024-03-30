#ifndef GENERADOR_PULSOS
#define GENERADOR_PULSOS

#include "InclusionTaskSchedulerDeclarations.h"
#include "INTERFAZ_Pulsable.h"
#include <Printable.h>
    class GeneradorPulsos : public Task, public Printable {
        private:
            Pulsable* pulsable;
    
        public:
            GeneradorPulsos(Pulsable* pulsable, long msSemiCiclo, long numPulsos, Scheduler* planif);
    
            void enableNumPulsos(long cant);
            void enablePeriodo(long ms);
            void enableFrecuencia(long hz);
        
            bool OnEnable() override;
            bool Callback() override;
            void OnDisable() override;
        
            size_t printTo(Print& impresora) const override;
    };
#endif

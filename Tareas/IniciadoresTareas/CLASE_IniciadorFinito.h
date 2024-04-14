#ifndef INICIADOR_FINITO
#define INICIADOR_FINITO

#include "CLASE_IniciadorTareas.h"
#include "../../Utils/CLASE_Contador.h"
    class IniciadorFinito : public IniciadorTareas {
        private:
            Contador<size_t> contIteraciones;
        
        public:
            IniciadorFinito(unsigned long msEntreIniciaciones, unsigned long numIniciaciones, Scheduler* planif, Task *tarea);
            
            bool OnEnable(void) override;
            bool deboFinalizar(void) override;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print& impresora) const override;
    };
#endif

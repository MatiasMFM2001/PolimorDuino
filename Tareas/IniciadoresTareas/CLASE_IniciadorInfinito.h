#ifndef INICIADOR_INFINITO
#define INICIADOR_INFINITO

#include "CLASE_IniciadorTareas.h"
    class IniciadorInfinito : public IniciadorTareas {
        public:
            IniciadorInfinito(unsigned long msEntreIniciaciones, Scheduler *planif, Task *tarea);
            
            bool deboFinalizar(void) override;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override;
    };
#endif

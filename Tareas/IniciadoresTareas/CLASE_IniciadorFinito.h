#ifndef INICIADOR_FINITO
#define INICIADOR_FINITO

#include "CLASE_IniciadorTareas.h"
#include "../../Utils/CLASE_Contador.h"
    /**
     * @brief Tarea que permite iniciar la ejecución de otra tarea, cada cierta
     *  cantidad de tiempo, una cantidad finita de veces.
     */
    class IniciadorFinito : public IniciadorTareas {
        private:
            /**
             * @brief El contador que almacena la cantidad de iniciaciones
             *  restantes.
             */
            Contador<size_t> contIteraciones;
        
        public:
            /**
             * @brief Construye un PinEntradaAnalogica, con el número de pin,
             *  configuración de inversión y estado inicial especificados.
             *
             * @param numPin El número de pin especificado.
             * @param invertir @c true para invertir el funcionamiento,
             *  @c false para el caso contrario.
             */
            IniciadorFinito(unsigned long msEntreIniciaciones, unsigned long numIniciaciones, Scheduler *planif, Task *tarea);
            
            /**
             * @brief Reinicia el contador de iteraciones.
             *
             * @returns @c true para indicar que la tarea debería permanecer
             *  habilitada.
             */
            bool OnEnable(void) override;

            /**
             * @brief Decrementa al contador de iteraciones en @c 1.
             *
             * @returns @c true si el valor de @c contIteraciones es @c 0,
             *  @c false en caso contrario.
             */
            bool deboFinalizar(void) override;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override;
    };
#endif

#ifndef CLASE_AUTO_FLUSHER
#define CLASE_AUTO_FLUSHER

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>
#include <Print.h>
    /**
     * @brief Tarea que permite forzar periódicamente la impresión de los datos
     * 	encolados en la impresora especificada.
     */
    class AutoFlusher : public Task {
        private:
			/** @brief Puntero a la impresora. */
            Print* impresora;
        
        public:
            /**
             * @brief Construye un AutoFlusher, con la impresora, tiempo de
             *  espera y scheduler especificados.
             * 
             * @param impresora La impresora especificada (que no debería ser
             *  nula).
             * @param msEntreLlamados La cantidad mínima de milisegundos a
             *  esperar entre una impresión y la siguiente.
             * @param planif El planificador de tareas especificado (que puede
             *  ser nulo).
             */
            AutoFlusher(Print* impresora, long msEntreLlamados, Scheduler* planif);
        
			/**
			 * @brief Ejecuta la impresión periódica.
			 * 
			 * @returns @code true para indicar que la ejecución de la tarea fue
			 *  "productiva".
			 */
            bool Callback(void) override;
    };
#endif

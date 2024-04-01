#ifndef MEDIDOR
#define MEDIDOR

#include "InclusionLog4Arduino.h"
    /**
     * @brief Define una interfaz para los objetos que puedan medir parámetros,
     *  realizando acciones con los valores medidos.
     * 
     * @tparam TResultado El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename TResultado>
    class Medidor {
        protected:
            /**
             * @brief Usa el valor medido para imprimirlo en el log, y ejecutar
             *  el @code Callback().
             * 
             * @param ingr El valor medido.
             */
            void ejecutarCallback(TResultado ingr) {
                FLOGS("MEDIDOR - Ejecutando ejecutarCallback()");
                LOGS(ingr);
                this -> Callback(ingr);
            }
        
        public:
            /**
             * @brief Realiza acciones con el valor medido.
             * 
             * @param valor El valor medido.
             */
            virtual void Callback(TResultado valor) = 0;
    };
#endif

#ifndef MEDIDOR
#define MEDIDOR

#include "InclusionLog4Arduino.h"
    /**
     * @brief Define una interfaz para los objetos que puedan medir parámetros,
     *  realizando acciones con los valores medidos.
     * 
     * @tparam TResultado El tipo de dato que almacena el resultado de una
     *  medición.
     * @tparam FLogger La función encargada de imprimir en logs el valor medido.
     */
    template <typename TResultado, void (*FLogger)(TResultado&)>
    class Medidor {
        protected:
            const __FlashStringHelper *nombre;
            //TResultado resultado;
        
            /**
             * @brief Usa el valor medido para imprimirlo en el log, y ejecutar
             *  el @code Callback().
             * 
             * @param ingr El valor medido.
             */
            void ejecutarCallback(TResultado ingr) {
                LOG("MEDIDOR \"%S\" - Ejecutando Callback() con valor:", this -> nombre);
                FLogger(ingr);
                this -> Callback(ingr);
            }
        
        public:
            Medidor(const __FlashStringHelper *nombre)
                : nombre(nombre)
            {}
        
            virtual void iniciarMedicion() = 0;
        
            /**
             * @brief Realiza acciones con el valor medido.
             * 
             * @param valor El valor medido.
             */
            virtual void Callback(TResultado valor) = 0;
    };
#endif

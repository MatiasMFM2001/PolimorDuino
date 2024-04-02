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
        private:
            CallbackResultado<TResultado> *callback;
            
        protected:
            const __FlashStringHelper *nombre;
        
            /**
             * @brief Usa el valor medido para imprimirlo en el log, y ejecutar
             *  el @code callback.
             * 
             * @param ingr El valor medido.
             */
            void ejecutarCallback(TResultado ingr) {
                LOG("MEDIDOR \"%S\" - Ejecutando callback.notificar() con valor:", this -> nombre);
                FLogger(ingr);
                this -> callback -> notificar(ingr);
            }
        
        public:
            Medidor(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback)
                : nombre(nombre), callback(callback)
            {}
        
            virtual void iniciarMedicion() = 0;
            virtual void finalizarMedicion() = 0;
    };
#endif

#ifndef MEDIDOR
#define MEDIDOR

#include "../Inclusiones/InclusionLog4Arduino.h"
    /**
     * @brief Define una interfaz para los objetos que puedan medir parámetros,
     *  realizando acciones con los valores medidos.
     * 
     * @tparam TResultado El tipo de dato que almacena el resultado de una
     *  medición.
     * @tparam FLogger La función encargada de imprimir en logs el valor medido.
     */
    template <typename TResultado, void (*FLogger)(TResultado&)>
    class Medidor : public Printable {
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
            void finalizarMedicion(TResultado ingr) {
                LOG("MEDIDOR \"%S\" - Ejecutando callback.notificar() con valor:", this -> nombre);
                FLogger(ingr);
                this -> callback -> notificar(ingr);
            }
        
        public:
            Medidor(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback)
                : callback(callback), nombre(nombre)
            {}
        
            virtual void iniciarMedicion() = 0;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print& impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "Medidor", callback, nombre);
            }
    };
#endif

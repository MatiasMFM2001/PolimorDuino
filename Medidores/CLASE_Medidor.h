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
            const __FlashStringHelper *nombre;
        
        public:
            Medidor(const __FlashStringHelper *nombre)
                : nombre(nombre)
            {}
        
            virtual void iniciarMedicion() = 0;
            virtual void finalizarMedicion() = 0;
    };
#endif

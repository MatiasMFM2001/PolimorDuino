#ifndef SALIDA_DIGITAL
#define SALIDA_DIGITAL

#include "CLASE_Salida.h"
#include "../../Utils/CLASE_Pulsable.h"
#include "../TIPOS_EnterosAnalogicos.h"
    class SalidaDigital : public Salida<BOOL_1_BIT>, public Pulsable {
        public:
            SalidaDigital(bool invertir, bool estadoInicial);
            
            void setEstado(bool valor) override;
            
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

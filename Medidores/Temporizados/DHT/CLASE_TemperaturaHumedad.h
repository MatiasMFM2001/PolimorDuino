/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TEMPERATURA_HUMEDAD
#define TEMPERATURA_HUMEDAD

#include <math.h>
#include <Printable.h>
#include <Print.h>

#define NO_DEFINIDA (-INFINITY)
    class TemperaturaHumedad : public Printable {
        private:
            float temperatura;
            float humedad;
        
        public:
            TemperaturaHumedad(float temperatura = NO_DEFINIDA, float humedad = NO_DEFINIDA);
            
            void setTemperatura(float ingr);
            float getTemperatura(void);
            bool tieneTemperatura(void);
            
            void setHumedad(float ingr);
            float getHumedad(void);
            bool tieneHumedad(void);
            
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

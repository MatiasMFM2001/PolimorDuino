/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TERMOMETRO_HUMEDOMETRO_DHT
#define TERMOMETRO_HUMEDOMETRO_DHT

#include "../../../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include "../CLASE_MedidorTemporizado.h"
#include "CLASE_TemperaturaHumedad.h"
#include <DHT.h>
#include "../../../Logger/FuncionesLoggers.h"
    template <bool MEDIR_TEMPERATURA, bool MEDIR_HUMEDAD, void (*F_LOGGER)(TemperaturaHumedad&) = imprimir>
    class TermometroHumedometroDHT : public MedidorTemporizado<TemperaturaHumedad, F_LOGGER> {
        private:
            DHT *sensor;
            
        public:
            TermometroHumedometroDHT(const __FlashStringHelper *nombre, CallbackResultado<TemperaturaHumedad> *callback, Scheduler *planif, DHT *sensor)
                : MedidorTemporizado<TemperaturaHumedad, F_LOGGER>(nombre, callback, 2 * TASK_SECOND, planif)
                , sensor(sensor)
            {}

            virtual void iniciarMedicion(void) override {
                this -> sensor -> begin();
            }

            /**
             * @returns El valor de la última medición realizada, de temperatura
             *  y/o de humedad, según @c MEDIR_TEMPERATURA y @c MEDIR_HUMEDAD.
             */
            virtual TemperaturaHumedad getResultado(void) override {
                TemperaturaHumedad salida;
                
                if (MEDIR_HUMEDAD) {
                    salida.setHumedad(this -> sensor -> readHumidity());
                }
                
                if (MEDIR_TEMPERATURA) {
                    salida.setTemperatura(this -> sensor -> readTemperature(false));
                }
                
                return salida;
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "TermometroHumedometroDHT") + SUPERCLASES_A_JSON(impresora, (MedidorTemporizado<TemperaturaHumedad, F_LOGGER>));
            }
    };
#endif

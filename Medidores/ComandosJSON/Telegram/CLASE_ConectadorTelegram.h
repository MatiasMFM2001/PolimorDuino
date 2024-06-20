/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONECTADOR_TELEGRAM
#define CONECTADOR_TELEGRAM

#include "../../Instantaneos/CLASE_MedidorInstantaneo.h"
#include "CLASE_ClienteTelegram.h"
    /**
     * @brief 
     */
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, size_t CAPACIDAD_MENSAJE, void (*F_LOGGER_CLIENTE)(CanalBidireccional<Stream, Print>&) = nullptr, void (*F_LOGGER)(WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>>&) = nullptr>
    class ConectadorTelegram : public MedidorInstantaneo<WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>>, F_LOGGER>, public CondicionResultado<WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>>>, public CondicionResultado<IniciadorTareas> {
        private:
            ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE> *bot;
        
        public:
            ConectadorTelegram(const __FlashStringHelper *nombre, CallbackResultado<WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>>> *callback, Scheduler *planif, ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE> *bot)
                : MedidorInstantaneo<WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>>, F_LOGGER>(nombre, callback, planif, this)
                , bot(bot)
            {}
            
            WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>> getResultado(void) override {
                return WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>>(this -> bot);
            }
            
            bool esValido(WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>> &resultado) override {
                bool retorno = resultado.getDato().conectarseATelegram();
                CLOG_REFERENCIA_IMPRESORA(Serial, "ESTADO DE INICIACIÓN =", retorno ? "true" : "false");
                
                return retorno;
            }
            
            bool esValido(IniciadorTareas &resultado) override {
                bool retorno = (resultado.getRunCounter() > 1) && (this -> bot -> conectarseATelegram());
                
                CLOG_REFERENCIA_IMPRESORA(Serial, "ESTADO DE CONEXION =", retorno ? "true" : "false");
                return retorno;
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "ConectadorTelegram") + SUPERCLASES_A_JSON(impresora, (Medidor<WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>>, F_LOGGER>));
            }
    };
#endif

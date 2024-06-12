/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONECTADOR_TELEGRAM_ASINCRONICO
#define CONECTADOR_TELEGRAM_ASINCRONICO

#include "../Instantaneos/CLASE_MedidorInstantaneo.h"
#include "../../Inclusiones/InclusionAsyncTelegram2.h"
    /**
     * @brief 
     */
    template <void (*F_LOGGER)(WrapperPuntero<AsyncTelegram2>&) = nullptr>
    class ConectadorTelegramAsincronico : public MedidorInstantaneo<WrapperPuntero<AsyncTelegram2>, F_LOGGER>, public CondicionResultado<WrapperPuntero<AsyncTelegram2>>, public CondicionResultado<> {
        private:
            AsyncTelegram2 *bot;
        
        public:
            ConectadorTelegramAsincronico(const __FlashStringHelper *nombre, CallbackResultado<WrapperPuntero<AsyncTelegram2>> *callback, Scheduler *planif, AsyncTelegram2 *bot)
                : MedidorInstantaneo<WrapperPuntero<AsyncTelegram2>, F_LOGGER>(nombre, callback, planif, this)
                , bot(bot)
            {}
            
            WrapperPuntero<AsyncTelegram2> getResultado(void) override {
                return WrapperPuntero(this -> bot);
            }
            
            bool esValido(WrapperPuntero<AsyncTelegram2> &resultado) override {
                bool retorno = resultado.getDato().checkConnection();
                LOG("ESTADO DE INICIACIÓN = %s", retorno ? "true" : "false");
                
                return retorno;
            }
            
            bool esValido(void) override {
                bool retorno = this -> bot -> begin();
                
                LOG("ESTADO DE CONEXION = %s", retorno ? "true" : "false");
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
                return OBJETO_A_JSON(impresora, "ConectadorTelegramAsincronico") + SUPERCLASES_A_JSON(impresora, (Medidor<WrapperPuntero<AsyncTelegram2>, F_LOGGER>));
            }
    };
#endif

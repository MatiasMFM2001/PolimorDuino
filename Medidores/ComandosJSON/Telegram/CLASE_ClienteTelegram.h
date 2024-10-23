/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CLIENTE_TELEGRAM
#define CLIENTE_TELEGRAM

#include "../../Instantaneos/CLASE_MedidorInstantaneo.h"
#include <Stream.h>
#include "../STRUCT_CanalBidireccional.h"
#include "../../../Utils/FuncionesGlobales.h"
#include "CLASE_MensajeTelegram.h"
#include <LoopbackStream.h>
#include <DEVNULL.h>
#include "CLASE_ImpresoraTelegram.h"
#include "../../Callbacks/INTERFAZ_CallbackResultadoMutable.h"
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, size_t CAPACIDAD_MENSAJE, void (*F_LOGGER)(CanalBidireccional<Stream, Print>&) = nullptr>
    class ClienteTelegram : public MedidorInstantaneo<CanalBidireccional<Stream, Print>, F_LOGGER>, public CondicionResultado<CanalBidireccional<Stream, Print>> {
        private:
            Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS> canalesPermitidos;
            LoopbackStream stream;
            ImpresoraTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER> impresora;
            DEVNULL streamNulo;
            
        public:
            ClienteTelegram(const __FlashStringHelper *nombre, CallbackResultado<CanalBidireccional<Stream, Print>> *callback, Scheduler *planif, size_t capacidadBuffer, bool enviarRespuestasSiByteIgualA, byte byteEnvioAutomatico)
                : MedidorInstantaneo<CanalBidireccional<Stream, Print>, F_LOGGER>(nombre, callback, planif, this)
                , canalesPermitidos(Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS>()), stream(LoopbackStream(capacidadBuffer)), impresora(ImpresoraTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER>(this, 0, enviarRespuestasSiByteIgualA, byteEnvioAutomatico))
            {}
            
            virtual MensajeTelegram<CAPACIDAD_MENSAJE> recibirMensaje(void) = 0;
            virtual bool enviarMensaje(MensajeTelegram<CAPACIDAD_MENSAJE> &ingr) = 0;
            virtual bool conectarseATelegram(void) = 0;
            virtual StringEstatica<32> getNombreUsuario(void) = 0;
            
            CanalBidireccional<Stream, Print> getResultado(void) override {
                MensajeTelegram<CAPACIDAD_MENSAJE> mensaje = this -> recibirMensaje();
                
                if (!mensaje.esValido()) {
                    FLOGS("ADVERTENCIA: Se descartó el mensaje recibido, porque no es válido (o está vacío)");
                    return {this -> streamNulo, this -> streamNulo};
                }
                
                if (!mensaje.esMensajeTexto()) {
                    CLOG_REFERENCIA_IMPRESORA(this -> impresora, F("ADVERTENCIA: Se descartó el mensaje recibido, porque no es de texto"));
                    return {this -> streamNulo, this -> streamNulo};
                }
                
                int64_t idCanal = mensaje.getIDCanal();
                
                if (!contiene(this -> canalesPermitidos, idCanal)) {
                    CLOG_REFERENCIA_IMPRESORA(this -> impresora, F("ADVERTENCIA: Se descartó el mensaje recibido, porque el canal"), idCanal, F("no está en el conjunto de canales permitidos"));
                    return {this -> streamNulo, this -> streamNulo};
                }
                
                this -> stream.clear();
                StringEstatica<CAPACIDAD_MENSAJE> &texto = mensaje.getContenido();
                
                size_t tamanioTexto = texto.getLongitud();
                size_t tamanioBuffer = (this -> stream.availableForWrite());
                
                if (tamanioTexto > tamanioBuffer) {
                    CLOG_REFERENCIA_IMPRESORA(this -> impresora, F("ERROR: La cadena leida (de"), tamanioTexto, F("caracteres) no entra en el LoopbackStream de"), tamanioBuffer, F("caracteres"));
                    return {this -> streamNulo, this -> streamNulo};
                }
                
                this -> stream.print(texto.getContenidoConstante());
                this -> impresora.reiniciarBuffer(idCanal);
                
                return {this -> stream, this -> impresora};
            }
            
            bool esValido(const CanalBidireccional<Stream, Print> &resultado) const override {
                int numBytesDisponibles = resultado.entrada.available();
                LOG("resultado.entrada.available() = %d", numBytesDisponibles);

                return (numBytesDisponibles > 0);
            }
            
            void setCanalesPermitidos(Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS> &ingr) {
                this -> canalesPermitidos = ingr;
            }
            
            Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS> &getCanalesPermitidos(void) {
                return (this -> canalesPermitidos);
            }
            
            template <typename... T_ARGUMENTOS>
            void enviarMensajeCanalesPermitidos(CallbackResultadoMutable<ImpresoraTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER>, T_ARGUMENTOS...> &enviador, T_ARGUMENTOS&... argumentos) {
                for (int64_t selec: this -> canalesPermitidos) {
                    ImpresoraTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER> impresora(this, selec);
                    enviador.notificar(impresora, argumentos...);
                }
            }
            
            template <typename... T_ARGUMENTOS>
            void enviarMensajeCanalesPermitidos(CallbackResultadoMutable<Print, T_ARGUMENTOS...> &enviador, T_ARGUMENTOS&... argumentos) {
                for (int64_t selec: this -> canalesPermitidos) {
                    ImpresoraTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER> impresora(this, selec);
                    enviador.notificar(impresora, argumentos...);
                }
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "ClienteTelegram") + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<CanalBidireccional<Stream, Print>, F_LOGGER>));
            }
    };
#endif

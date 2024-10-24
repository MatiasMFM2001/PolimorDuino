/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef IMPRESORA_TELEGRAM
#define IMPRESORA_TELEGRAM

template <size_t CAPACIDAD_CANALES_PERMITIDOS, size_t CAPACIDAD_MENSAJE, void (*F_LOGGER)(CanalBidireccional<Stream, Print>&)>
class ClienteTelegram;

#include <Print.h>
#include "CLASE_ClienteTelegram.h"
    /**
     * @brief 
     */
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, size_t CAPACIDAD_MENSAJE, void (*F_LOGGER_CLIENTE)(CanalBidireccional<Stream, Print>&) = nullptr>
    class ImpresoraTelegram : public Print {
        private:
            ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE> *cliente;
            MensajeTelegram<CAPACIDAD_MENSAJE> buffer;
            
            bool enviarRespuestasSiByteIgualA;
            byte byteEnvioAutomatico;
            
        public:
            /**
             * @brief Construye un BufferDatos, con el array vacío y la
             *  impresora especificada.
             * 
             * @param salida La impresora especificada (que puede ser nula).
             */
            ImpresoraTelegram(ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE> *cliente, int64_t idCanal, bool enviarRespuestasSiByteIgualA, byte byteEnvioAutomatico)
                : Print()
                , cliente(cliente), enviarRespuestasSiByteIgualA(enviarRespuestasSiByteIgualA), byteEnvioAutomatico(byteEnvioAutomatico)
            {
                this -> reiniciarBuffer(idCanal);
            }
        
            /**
             * @brief Escribe un byte en el buffer, si hay capacidad suficiente.
             * 
             * @param ingr El byte a escribir.
             * @returns @c 1 si hay capacidad, @c 0 en caso contrario.
             */
            size_t write(byte ingr) override {
                if (this -> buffer.estaLleno()) {
                    return 0;
                }
                
                if ((this -> enviarRespuestasSiByteIgualA) && (ingr == (this -> byteEnvioAutomatico))) {
                    this -> flush();
                    return 1;
                }
                
                this -> buffer.agregarFinal(ingr);
                return 1;
            }
            
            /**
             * @brief Si la impresora no es nula, le envía todos los datos
             *  almacenados y vacía el buffer.
             */
            void flush(void) override {
                this -> cliente -> enviarMensaje(this -> buffer);
                this -> buffer.vaciarContenido();
            }
            
            int availableForWrite(void) override {
                return this -> buffer.getCapacidadRestante();
            }
            
            void reiniciarBuffer(int64_t idCanal) {
                this -> buffer = MensajeTelegram<CAPACIDAD_MENSAJE>(nullptr, idCanal, true);
            }
            
            void setIDCanal(int64_t ingr) {
                this -> buffer.setIDCanal(ingr);
            }
            
            int64_t getIDCanal(void) {
                return (this -> buffer.getIDCanal());
            }
    };
#endif

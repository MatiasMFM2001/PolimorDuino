/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SOLICITUD_CON_PAYLOAD
#define SOLICITUD_CON_PAYLOAD

#include "CLASE_SolicitudSinPayload.h"
#include "../EstructurasDatos/Buffers/CLASE_BufferImpresora.h"
    template <size_t CAPACIDAD_MAPA_ARGUMENTOS, size_t CAPACIDAD_MAPA_ENCABEZADOS, size_t CAPACIDAD_URI_COMPLETA, size_t CAPACIDAD_BUFFER_PAYLOAD, typename T_CADENAS = __FlashStringHelper>
    class SolicitudConPayload : public SolicitudSinPayload<CAPACIDAD_MAPA_ARGUMENTOS, CAPACIDAD_MAPA_ENCABEZADOS, CAPACIDAD_URI_COMPLETA, T_CADENAS>, public Print {
        private:
            BufferImpresora<CAPACIDAD_BUFFER_PAYLOAD, uint8_t> buffer;
        
        protected:
            virtual int enviarSolicitudBajoNivel(HTTPClient &cliente, const char *metodoCopiado) override {
                return cliente.sendRequest(metodoCopiado, this -> buffer.getContenido(), this -> buffer.getLongitudBytes());
            }
        
        public:
            SolicitudConPayload(NetworkClient &clienteRed, CallbackResultado<HTTPClient, int> *callbackRecepcionRespuesta)
                : SolicitudSinPayload<CAPACIDAD_MAPA_ARGUMENTOS, CAPACIDAD_MAPA_ENCABEZADOS, CAPACIDAD_URI_COMPLETA, T_CADENAS>(clienteRed, callbackRecepcionRespuesta)
                , buffer(BufferImpresora<CAPACIDAD_BUFFER_PAYLOAD>())
            {}
            
            size_t write(byte ingr) override {
                if (!(this -> getEstado())) {
                    return 0;
                }
                
                return (this -> buffer.write(ingr));
            }
            
            void flush(void) override {
                this -> enviar();
                this -> buffer.vaciarContenido();
            }
    };
#endif

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SOLICITUD_SIN_PAYLOAD
#define SOLICITUD_SIN_PAYLOAD

#ifdef ESP8266
    #include <ESP8266HTTPClient.h>
    typedef WiFiClient NetworkClient;
#else
    #include <HTTPClient.h>
#endif

#include "../EstructurasDatos/Mapas/CLASE_ArrayMapa.h"
#include "../../Medidores/Callbacks/INTERFAZ_CallbackResultado.h"
#include <UrlEncode.h>
#include "../Pulsables/CLASE_Pulsable.h"
#include "../EstructurasDatos/Conjuntos/CLASE_AdaptadorFuncionComparadorIgualdad.h"
    template <size_t CAPACIDAD_MAPA_ARGUMENTOS, size_t CAPACIDAD_MAPA_ENCABEZADOS, size_t CAPACIDAD_URI_COMPLETA>
    class SolicitudSinPayload : public Pulsable {
        private:
            NetworkClient &clienteRed;
            CallbackResultado<HTTPClient, int> *callbackRecepcionRespuesta;
            
            const __FlashStringHelper *dominio;
            uint16_t puertoTCP;
            const __FlashStringHelper *uriRecurso;
            bool usarHTTPs;
            
            const __FlashStringHelper *metodoHTTP;
            
            AdaptadorFuncionComparadorIgualdad<const __FlashStringHelper *> adaptadorIgualdad;
            ArrayMapa<const __FlashStringHelper *, const __FlashStringHelper *, CAPACIDAD_MAPA_ARGUMENTOS> argumentos;
            ArrayMapa<const __FlashStringHelper *, const __FlashStringHelper *, CAPACIDAD_MAPA_ENCABEZADOS> encabezados;
        
        protected:
            virtual int enviarSolicitudBajoNivel(HTTPClient &cliente, const char *metodoCopiado) {
                return cliente.sendRequest(metodoCopiado);
            }
        
        public:
            SolicitudSinPayload(NetworkClient &clienteRed, CallbackResultado<HTTPClient, int> *callbackRecepcionRespuesta)
                : Pulsable(false, false)
                , clienteRed(clienteRed)
                , callbackRecepcionRespuesta(callbackRecepcionRespuesta)
                
                , adaptadorIgualdad(AdaptadorFuncionComparadorIgualdad<const __FlashStringHelper *>(&iguales))
                , argumentos(ArrayMapa<const __FlashStringHelper *, const __FlashStringHelper *, CAPACIDAD_MAPA_ARGUMENTOS>(&adaptadorIgualdad))
                , encabezados(ArrayMapa<const __FlashStringHelper *, const __FlashStringHelper *, CAPACIDAD_MAPA_ARGUMENTOS>(&adaptadorIgualdad))
            {}
            
            void settearDominio(const __FlashStringHelper *ingr) {
                this -> dominio = ingr;
            }
            
            void settearPuerto(const uint16_t ingr) {
                this -> puertoTCP = ingr;
            }
            
            void settearURI(const __FlashStringHelper *ingr) {
                this -> uriRecurso = ingr;
            }
            
            void settearHTTPs(const bool ingr) {
                this -> usarHTTPs = ingr;
            }
            
            void settearMetodo(const __FlashStringHelper *ingr) {
                this -> metodoHTTP = ingr;
            }
            
            bool agregarArgumento(const __FlashStringHelper *clave, const __FlashStringHelper *valor) {
                return (this -> argumentos.agregar(clave, valor));
            }
            
            bool agregarEncabezado(const __FlashStringHelper *clave, const __FlashStringHelper *valor) {
                return (this -> encabezados.agregar(clave, valor));
            }
            
            bool enviar(Print *salida = nullptr) {
                if (!(this -> getEstado())) {
                    CLOG_PUNTERO_IMPRESORA(salida, "SolicitudSinPayload::enviar() - Retornando false porque mi estado actual es FALSE");
                    return false;
                }
                
                HTTPClient cliente;
                cliente.setReuse(false);
                
                StringEstatica<CAPACIDAD_URI_COMPLETA> uriCompleta;
                uriCompleta.agregarFinal(this -> uriRecurso);
                uriCompleta.agregarFinal('?');
                
                for (const ElementoMapa<const __FlashStringHelper *, const __FlashStringHelper *> &selec: this -> argumentos) {
                    uriCompleta.agregarFinal(urlEncode(selec.getClave()));
                    uriCompleta.agregarFinal('=');
                    uriCompleta.agregarFinal(urlEncode(selec.getValor()));
                    
                    uriCompleta.agregarFinal('&');
                }
                
                CLOG_PUNTERO_IMPRESORA(salida, "SolicitudSinPayload::enviar() - URI completa =", uriCompleta);
                
                for (const ElementoMapa<const __FlashStringHelper *, const __FlashStringHelper *> &selec: this -> encabezados) {
                    cliente.addHeader(selec.getClave(), selec.getValor());
                }
                
                if (!cliente.begin(this -> clienteRed, this -> dominio, this -> puertoTCP, uriCompleta.getContenidoConstante(), this -> usarHTTPs)) {
                    CLOG_PUNTERO_IMPRESORA(salida, "SolicitudSinPayload::enviar() - ERROR: No se pudo iniciar el cliente HTTP(s)");
                    return false;
                }
                
                StringEstatica<8> metodoCopiado;
                AdaptadorStringImpresora adaptadorMetodo(&metodoCopiado);
                
                adaptadorMetodo.print(this -> metodoHTTP);
                CLOG_PUNTERO_IMPRESORA(salida, "SolicitudSinPayload::enviar() - metodoCopiado =", metodoCopiado);
                int retorno = (this -> enviarSolicitudBajoNivel(cliente, metodoCopiado.getContenidoConstante()));
                
                if (retorno < 0) {
                    CLOG_PUNTERO_IMPRESORA(salida, "SolicitudSinPayload::enviar() - ERROR: Al enviar la solicitud, se obtuvo el valor", retorno, '=', cliente.errorToString(retorno));
                    return false;
                }
                
                if (this -> callbackRecepcionRespuesta) {
                    this -> callbackRecepcionRespuesta -> notificar(cliente, retorno);
                }
                
                return true;
            }
            
            void setEstado(bool valor) override {
                this -> setEstadoActual(valor);
            }
    };
#endif

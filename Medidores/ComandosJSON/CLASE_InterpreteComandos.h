/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INTERPRETE_COMANDOS
#define INTERPRETE_COMANDOS

#define CLAVE_COMANDO "COMANDO"
#define CLAVE_ARGS "ARGS"

#include "../CLASE_Medidor.h"
#include "../Condiciones/CLASE_AdaptadorFuncionCondicion.h"
    /**
     * @brief 
     */
    template <size_t CAPACIDAD_JSON_FINAL, size_t CAPACIDAD_JSON_INTERMEDIO, size_t CAPACIDAD_STRING_COMANDO, void (*F_LOGGER)(JsonDocument&) = imprimir>
    class InterpreteComandos : public Medidor<JsonDocument, F_LOGGER>, public CallbackResultado<WrapperPuntero<Stream>> {
        public:
            InterpreteComandos(const __FlashStringHelper *nombre, CallbackResultado<JsonDocument> *callback, CondicionResultado<JsonDocument> *verificador = nullptr)
                : Medidor<JsonDocument, F_LOGGER>(nombre, callback, verificador)
            {}
            
            void iniciarMedicion(void) override {
            }
            
            void notificar(WrapperPuntero<Stream> &resultado) override {
                CLOG("InterpreteComandos - ESTADO ACTUAL = ", *this);
                
                StaticJsonDocument<CAPACIDAD_JSON_FINAL> documentoFinal;
                Stream &stream = resultado.getDato();
                
                while (true) {
                    switch (stream.peek()) {
                        case '/':
                            goto procesar;
                        
                        case -1:
                            return;
                        
                        default:
                            LOG("Caracter salteado = %c", stream.read());
                            break;
                    }
                }
                
                procesar:
                    FLOGS("Parseando comando...");
                    
                    StringEstatica<CAPACIDAD_STRING_COMANDO> bufferComando;
                    AdaptadorFuncionCondicion<int> detectorBlanco(&isSpace);
                    bufferComando.agregarCaracteresHasta(stream, detectorBlanco);
                    
                    LOG("Comando parseado = '%s'", bufferComando.getContenido());
                    documentoFinal[CLAVE_COMANDO] = bufferComando.getContenido();
                    
                    StaticJsonDocument<CAPACIDAD_JSON_INTERMEDIO> documentoIntermedio;
                    DeserializationError retorno = deserializeJson(documentoIntermedio, stream);
                    JsonArray array = documentoFinal.createNestedArray(CLAVE_ARGS);
                    
                    while ((retorno == DeserializationError::Ok) && !(documentoFinal.overflowed())) {
                        array.add(documentoIntermedio);
                        
                        CLOG("DOCUMENTO INTERMEDIO:");
                        imprimir(documentoIntermedio);
                        
                        retorno = deserializeJson(documentoIntermedio, stream);
                        
                        if (retorno != DeserializationError::Ok) {
                            LOG("ERROR: Deserializar un argumento del stream falló con el error %s.", retorno.c_str());
                        }
                    }
                
                    CLOG("DOCUMENTO FINAL:");
                    imprimir(documentoFinal);
                    this -> finalizarMedicion(documentoFinal);
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "InterpreteComandos") + SUPERCLASES_A_JSON(impresora, (Medidor<JsonDocument, F_LOGGER>));
            }
    };
#endif

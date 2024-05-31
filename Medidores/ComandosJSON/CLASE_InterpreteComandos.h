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
    /**
     * @brief 
     */
    template <size_t CAPACIDAD_JSON_FINAL, size_t CAPACIDAD_JSON_INTERMEDIO, void (*F_LOGGER)(JsonDocument&) = nullptr>
    class InterpreteComandos : public Medidor<JsonDocument, F_LOGGER>, public CallbackResultado<WrapperPuntero<Stream>> {
        public:
            InterpreteComandos(const __FlashStringHelper *nombre, CallbackResultado<JsonDocument> *callback, CondicionResultado<JsonDocument> *verificador = nullptr)
                : Medidor<JsonDocument, F_LOGGER>(nombre, callback, verificador)
            {}
            
            void iniciarMedicion(void) override {
            }
            
            void notificar(WrapperPuntero<Stream> &resultado) override {
                this -> printTo(*_log4arduino_target);
                
                StaticJsonDocument<CAPACIDAD_JSON_FINAL> documentoFinal;
                Stream &stream = resultado.getDato();
                
                while (true) {
                    switch (stream.peek()) {
                        case 0xFE:
                        case 0xFF:
                        case '\n':
                        case -1:
                        case '/':
                            LOG("Caracter salteado = %c", stream.read());
                            break;
                            
                        default:
                            goto procesar;
                    }
                }
                
                procesar:
                    FLOGS("Parseando JSON de comando...");
                    StaticJsonDocument<CAPACIDAD_JSON_INTERMEDIO> documentoIntermedio;
                    DeserializationError retorno = deserializeJson(documentoIntermedio, stream);
                    
                    LOG("JSON inicial parseado con retorno %d", retorno);
                    serializeJsonPretty(documentoIntermedio, *_log4arduino_target);
                    
                    if (retorno != DeserializationError::Ok) {
                        LOG("ERROR: Deserializar el comando del stream falló con el error %d.", retorno);
                        return;
                    }
                    
                    if (!documentoIntermedio.template is<const char *>()) {
                        FLOGS("ERROR: El comando deserializado no es una String.");
                        return;
                    }
                    
                    documentoFinal[CLAVE_COMANDO] = documentoIntermedio.template as<const char *>();
                    JsonArray array = documentoFinal.createNestedArray(CLAVE_ARGS);
                    
                    while ((retorno == DeserializationError::Ok) && !(documentoFinal.overflowed())) {
                        retorno = deserializeJson(documentoIntermedio, stream);
                        
                        LOG("JSON argumento parseado con retorno %d", retorno);
                        serializeJsonPretty(documentoIntermedio, *_log4arduino_target);
                        
                        if (retorno != DeserializationError::Ok) {
                            LOG("ERROR: Deserializar un argumento del stream falló con el error %d.", retorno);
                            continue;
                        }
                        
                        array.add(documentoIntermedio);
                    }
                
                    FLOGS("DOCUMENTO FINAL:");
                    serializeJsonPretty(documentoFinal, *_log4arduino_target);
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

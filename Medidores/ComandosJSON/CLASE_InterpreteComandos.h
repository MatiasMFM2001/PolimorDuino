/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TAREA_MEDIDORA
#define TAREA_MEDIDORA

#define CLAVE_COMANDO "COMANDO"
#define CLAVE_ARGS "ARGS"

#include "CLASE_Medidor.h"
    /**
     * @brief 
     */
    template <typename T_RESULTADO, size_t CAPACIDAD_JSON_FINAL, size_t CAPACIDAD_JSON_INTERMEDIO, void (*F_LOGGER)(JsonDocument&) = nullptr>
    class InterpreteComandos : public Medidor<JsonDocument, F_LOGGER>, public CallbackResultado<WrapperPuntero<Stream>> {
        public:
            InterpreteComandos(const __FlashStringHelper *nombre, CallbackResultado<JsonDocument> *callback)
                : Medidor<JsonDocument, F_LOGGER>(nombre, callback)
                , Task(msMedicion, TASK_ONCE, planif, false), verificador(verificador)
            {}
            
            void iniciarMedicion(void) override {
            }
            
            void notificar(WrapperPuntero<Stream> &resultado) override {
                StaticJsonDocument<CAPACIDAD_JSON_FINAL> documentoFinal;
                Stream stream = resultado.getDato();
                
                while (true) {
                    switch (stream.peek()) {
                        case 0xFE:
                        case 0xFF:
                        case '\n':
                        case -1:
                        case '/':
                            stream.read();
                            break;
                            
                        default:
                            goto procesar;
                    }
                }
                
                procesar:
                    StaticJsonDocument<CAPACIDAD_JSON_INTERMEDIO> documentoIntermedio;
                    DeserializationError retorno = deserializeJson(documentoIntermedio, stream);
                    
                    if (retorno != DeserializationError::Ok) {
                        LOG("ERROR: Deserializar el comando del stream falló con el error %d.", retorno);
                        return;
                    }
                    
                    if (!documentoIntermedio.is<char *>()) {
                        FLOGS("ERROR: El comando deserializado no es una String.");
                        return;
                    }
                    
                    documentoFinal[CLAVE_COMANDO] = documentoIntermedio.as<char *>();
                    JsonArray array = documentoFinal.createNestedArray(CLAVE_ARGS);
                    
                    while ((retorno == DeserializationError::Ok) && !(documentoFinal.overflowed())) {
                        retorno = deserializeJson(documentoIntermedio, stream);
                        
                        if (retorno != DeserializationError::Ok) {
                            LOG("ERROR: Deserializar un argumento del stream falló con el error %d.", retorno);
                            continue;
                        }
                        
                        array.add(documentoIntermedio);
                    }
                
                    this -> finalizarMedicion(documentoFinal);
            }
    };
#endif

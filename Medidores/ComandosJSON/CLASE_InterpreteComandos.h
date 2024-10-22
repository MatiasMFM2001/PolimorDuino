/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INTERPRETE_COMANDOS
#define INTERPRETE_COMANDOS

#define CLAVE_COMANDO F("COMANDO")
#define CLAVE_ARGS F("ARGS")

#include "../CLASE_Medidor.h"
#include "../Condiciones/CLASE_AdaptadorFuncionCondicion.h"
#include "STRUCT_CanalBidireccional.h"
#include "../../Utils/FuncionesGlobales.h"
    /**
     * @brief 
     */
    template <size_t CAPACIDAD_JSON_FINAL, size_t CAPACIDAD_JSON_INTERMEDIO, size_t CAPACIDAD_STRING_COMANDO, size_t CAPACIDAD_STRING_NUMERO, void (*F_LOGGER)(CanalBidireccional<JsonDocument, Print>&) = nullptr>
    class InterpreteComandos : public Medidor<CanalBidireccional<JsonDocument, Print>, F_LOGGER>, public CallbackResultado<CanalBidireccional<Stream, Print>> {
        public:
            InterpreteComandos(const __FlashStringHelper *nombre, CallbackResultado<CanalBidireccional<JsonDocument, Print>> *callback, CondicionResultado<CanalBidireccional<JsonDocument, Print>> *verificador = nullptr)
                : Medidor<CanalBidireccional<JsonDocument, Print>, F_LOGGER>(nombre, callback, verificador)
            {}
            
            void iniciarMedicion(void) override {
            }
            
            void notificar(const CanalBidireccional<Stream, Print> &resultado) override {
                CLOG(F("InterpreteComandos - ESTADO ACTUAL = "), *this);
                
                StaticJsonDocument<CAPACIDAD_JSON_FINAL> documentoFinal;
                Stream &stream = resultado.entrada;
                
                while (true) {
                    switch (stream.peek()) {
                        case '/':
                            goto procesar;
                        
                        case -1:
                            return;
                        
                        default:
                            LOG("Caracter salteado = '%c'", stream.read());
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
                    JsonArray array = documentoFinal.createNestedArray(CLAVE_ARGS);
                    
                    bool parseadoCorrectamente = parsearArgumento<CAPACIDAD_STRING_NUMERO>(stream, documentoIntermedio);
                    
                    while (parseadoCorrectamente && !(documentoFinal.overflowed())) {
                        array.add(documentoIntermedio);
                        parseadoCorrectamente = parsearArgumento<CAPACIDAD_STRING_NUMERO>(stream, documentoIntermedio);
                    }
                
                    FLOGS("DOCUMENTO FINAL:");
                    imprimir(documentoFinal);
                    
                    CanalBidireccional<JsonDocument, Print> salida = {documentoFinal, resultado.salida};
                    this -> finalizarMedicion(salida);
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "InterpreteComandos") + SUPERCLASES_A_JSON(impresora, (Medidor<CanalBidireccional<JsonDocument, Print>, F_LOGGER>));
            }
    };
#endif

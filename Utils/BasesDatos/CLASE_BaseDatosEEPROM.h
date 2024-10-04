/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BASE_DATOS_EEPROM
#define BASE_DATOS_EEPROM

#define DIRECCION_NUM_BYTES (0)
#define DIRECCION_DOCUMENTO (DIRECCION_NUM_BYTES + sizeof(size_t))

//#define GET_VALOR_SETTEANDO(clave, valorPredeterminado, salida) \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatosEEPROM::getValorSetteando('", clave, "') con la BD corrupta. Se retornará el valor predeterminado"); \
        return valorPredeterminado; \
    } \
 \
    if (!(this -> documento.containsKey(clave))) { \
        this -> setValor(clave, valorPredeterminado); \
    } \
 \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se corrompió la BD tras ejecutar BaseDatosEEPROM::getValorSetteando('", clave, "')"); \
 \
        if (!(this -> documento.containsKey(clave))) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor predeterminado"); \
            return valorPredeterminado; \
        } \
    }

#define DEFINIR_LEER_BAJO_NIVEL_BD_EEPROM(T_VALOR) \
    DEFINIR_METODO_BD(leerBajoNivel, bool,, const char *clave, T_VALOR &variableASobreescribir) { \
        variableASobreescribir = (this -> documento[clave]); \
        return true; \
    }

#define DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_EEPROM(T_VALOR) \
    DEFINIR_METODO_BD(escribirBajoNivel, bool,, char *copiaClave, T_VALOR copiaValor) { \
        this -> documento.garbageCollect(); \
        this -> documento[copiaClave] = copiaValor; \
        this -> documento.garbageCollect(); \
 \
        if (this -> documento.overflowed()) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ERROR: Al intentar insertar la clave '", copiaClave, "', falló porque el StaticJsonDocument<", CAPACIDAD_JSON, "> se llenó"); \
            return false; \
        } \
 \
        size_t tamanioSerializado = this -> medirSerializado(); \
        size_t tamanioEEPROM = (this -> eeprom -> length() - DIRECCION_DOCUMENTO + 1); \
 \
        if (tamanioSerializado > tamanioEEPROM) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Tras insertar la clave '", copiaClave, "', el documento serializado queda de tamaño ", tamanioSerializado, " y no entra en la EEPROM (de capacidad ", tamanioEEPROM, ')'); \
            return false; \
        } \
 \
        CLOG_PUNTERO_IMPRESORA(salida, "BaseDatosEEPROM::escribirBajoNivel('", copiaClave, "') finalizó correctamente"); \
        return true; \
    }

#include "CLASE_LectorEEPROM.h"
#include "CLASE_EscritorEEPROM.h"
#include <EEPROM.h>
#include <StreamUtils.h>
#include "CLASE_BaseDatos.h"
    template <size_t CAPACIDAD_JSON, size_t MAX_LONGITUD_CLAVES, size_t MAX_LONGITUD_STRINGS, typename T_EEPROM = EEPROMClass>
    class BaseDatosEEPROM : public BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS> {
        private:
            T_EEPROM *eeprom;
            StaticJsonDocument<CAPACIDAD_JSON> documento;
        
        protected:
             bool inicializarBajoNivel(void) override {
                size_t numBytesUsados;
                this -> eeprom -> get(DIRECCION_NUM_BYTES, numBytesUsados);
                
                LOG("BaseDatosEEPROM::inicializarBajoNivel() - numBytesUsados = %d", numBytesUsados);
                
                if (numBytesUsados > (this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1)) {
                    FLOGS("ERROR: La cantidad de bytes leidos es mayor a la posible de almacenar en la EEPROM");
                    return false;
                }
                
                //LectorEEPROM lector(DIRECCION_DOCUMENTO, this -> eeprom, numBytesUsados);
                EepromStream lector(DIRECCION_DOCUMENTO, this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1);
                DeserializationError retorno = deserializeMsgPack(this -> documento, lector);
                
                if (retorno != DeserializationError::Ok) {
                    LOG("ERROR: Deserializar el MessagePack de la EEPROM falló con el error %s", retorno.c_str());
                    return false;
                }
                
                if (!(this -> documento.template is<JsonObject>())) {
                    FLOGS("ADVERTENCIA: Reiniciando documento leído porque no es un objeto JSON");
                    this -> documento.clear();
                }
                
                return true;
            }
            
            FOR_EACH(DEFINIR_LEER_BAJO_NIVEL_BD_EEPROM, TIPOS_NATIVOS_BD);
            FOR_EACH(DEFINIR_LEER_BAJO_NIVEL_BD_EEPROM, TIPOS_CONVERTIBLES_BD);
            
            FOR_EACH(DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_EEPROM, TIPOS_NATIVOS_BD);
            FOR_EACH(DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_EEPROM, TIPOS_CONVERTIBLES_BD);
            
            bool guardarBajoNivel(Print *salida) override {
                //EscritorEEPROM escritor(DIRECCION_DOCUMENTO, this -> eeprom);
                CLOG_PUNTERO_IMPRESORA(salida, "DIRECCION_DOCUMENTO = ", DIRECCION_DOCUMENTO, "; this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1 = ", this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1);
                EepromStream escritor(DIRECCION_DOCUMENTO, this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1);
                size_t tamanioEscrito = serializeMsgPack(this -> documento, escritor);
                
                this -> eeprom -> put(DIRECCION_NUM_BYTES, tamanioEscrito);
                escritor.flush();
                
                StaticJsonDocument<CAPACIDAD_JSON> documentoReleido;
                size_t numBytesUsadosReleido;
                this -> eeprom -> get(DIRECCION_NUM_BYTES, numBytesUsadosReleido);
                
                CLOG_PUNTERO_IMPRESORA(salida, "BaseDatosEEPROM::guardarBajoNivel() - numBytesUsadosReleido = ", numBytesUsadosReleido);
                
                if (numBytesUsadosReleido > (this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1)) {
                    CLOG_PUNTERO_IMPRESORA(salida, "ERROR: La cantidad de bytes releidos es mayor a la posible de almacenar en la EEPROM");
                    return false;
                }

                DeserializationError retorno = deserializeMsgPack(this -> documento, escritor);
                
                if (retorno != DeserializationError::Ok) {
                    CLOG_PUNTERO_IMPRESORA(salida, "ERROR: Re-deserializar el MessagePack de la EEPROM falló con el error", retorno.c_str());
                    return false;
                }
                
                if (!(this -> documento.template is<JsonObject>())) {
                    CLOG_PUNTERO_IMPRESORA(salida, "ERROR: El documento releido no es un objeto JSON");
                    return false;
                }
                
                CLOG_PUNTERO_IMPRESORA(salida, "BaseDatosEEPROM::guardarBajoNivel() - Guardados", tamanioEscrito, '/', this -> eeprom -> length(), "bytes correctamente");
                return true;
            }
            
            bool contieneClaveBajoNivel(const char *ingr) override {
                return (this -> documento.containsKey(ingr));
            }
        
        public:
            BaseDatosEEPROM(T_EEPROM *eeprom, size_t version, CallbackResultadoMutable<BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS>> *migrador, bool leerAlInicializar = false)
                : BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS>(version, migrador, leerAlInicializar)
                , eeprom(eeprom), documento(StaticJsonDocument<CAPACIDAD_JSON>())
            {}
            
            size_t medirSerializado(void) {
                return measureMsgPack(this -> documento);
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "BaseDatosEEPROM") + SUPERCLASES_A_JSON(impresora, (BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS>))
                    + impresora.println()
                    + serializeJsonPretty(this -> documento, impresora);
            }
    };
#endif

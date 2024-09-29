/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BASE_DATOS_EEPROM
#define BASE_DATOS_EEPROM

#define DIRECCION_NUM_BYTES (0)
#define DIRECCION_DOCUMENTO (DIRECCION_NUM_BYTES + sizeof(size_t))

#define CLAVE_VERSION "VERSION"

#define GET_VALOR(clave, salida) \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatosEEPROM::getValor('", clave, "') con la BD corrupta. Se retornará el valor indeterminado"); \
 \
        if (this -> documento.containsKey(clave)) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor previamente almacenado en esa clave."); \
        } \
        else { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor predeterminado para ese tipo de datos."); \
        } \
    }

#define GET_VALOR_SETTEANDO(clave, valorPredeterminado, salida) \
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

#define SET_VALOR(clave, copiaValor, CAPACIDAD_STRINGS, salida) \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatosEEPROM::setValor('", clave, "') con la BD corrupta"); \
        return false; \
    } \
 \
    StringEstatica<CAPACIDAD_STRINGS> copiaClave(clave); \
 \
    CLOG_PUNTERO_IMPRESORA(salida, "Escribiendo BaseDatosEEPROM::setValor('%s') = %s", clave, copiaClave.getContenido()); \
 \
    this -> documento.garbageCollect(); \
    this -> documento[copiaClave.getContenido()] = copiaValor; \
    this -> documento.garbageCollect(); \
 \
    if (this -> documento.overflowed()) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ERROR: Al intentar insertar la clave '", clave, "', falló porque el StaticJsonDocument<", CAPACIDAD_JSON, "> se llenó"); \
        this -> estaCorrupta = true; \
        return false; \
    } \
 \
    size_t tamanioSerializado = this -> medirSerializado(); \
    size_t tamanioEEPROM = (this -> eeprom -> length() - DIRECCION_DOCUMENTO + 1); \
 \
    if (tamanioSerializado > tamanioEEPROM) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Tras insertar la clave '", clave, "', el documento serializado queda de tamaño ", tamanioSerializado, " y no entra en la EEPROM (de capacidad ", tamanioEEPROM, ')'); \
        this -> estaCorrupta = true; \
        return false; \
    } \
 \
    CLOG_PUNTERO_IMPRESORA(salida, "BaseDatosEEPROM::setValor('", clave, "') finalizó correctamente"); \
    return true; \

#include <ArduinoJson.h>
#include "../FuncionesGlobales.h"
#include "CLASE_LectorEEPROM.h"
#include "CLASE_EscritorEEPROM.h"
#include <EEPROM.h>
#include "../../Medidores/Callbacks/INTERFAZ_CallbackResultado.h"
#include <Printable.h>
#include "../CLASE_StringEstatica.h"
#include "../../Logger/FuncionesLoggers.h"
#include <StreamUtils.h>
    template <size_t CAPACIDAD_JSON, size_t CAPACIDAD_STRINGS, typename T_EEPROM = EEPROMClass>
    class BaseDatosEEPROM : public Inicializable, public Printable {
        private:
            T_EEPROM *eeprom;
            StaticJsonDocument<CAPACIDAD_JSON> documento;
            bool leerAlInicializar;
            bool estaCorrupta;
            size_t version;
            CallbackResultado<JsonDocument> *migrador;
            
        public:
            BaseDatosEEPROM(T_EEPROM *eeprom, size_t version, CallbackResultado<JsonDocument> *migrador, bool leerAlInicializar = false)
                : eeprom(eeprom), documento(StaticJsonDocument<CAPACIDAD_JSON>()), leerAlInicializar(leerAlInicializar), estaCorrupta(false), version(version), migrador(migrador)
            {}
            
            void inicializar(void) override {
                if (!(this -> leerAlInicializar)) {
                    return;
                }
                
                size_t numBytesUsados;
                this -> eeprom -> get(DIRECCION_NUM_BYTES, numBytesUsados);
                
                LOG("BaseDatosEEPROM::inicializar() - numBytesUsados = %d", numBytesUsados);
                
                if (numBytesUsados > (this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1)) {
                    FLOGS("ERROR: La cantidad de bytes leidos es mayor a la posible de almacenar en la EEPROM");
                    this -> estaCorrupta = true;
                    
                    return;
                }
                
                //LectorEEPROM lector(DIRECCION_DOCUMENTO, this -> eeprom, numBytesUsados);
                EepromStream lector(DIRECCION_DOCUMENTO, this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1);
                DeserializationError retorno = deserializeMsgPack(this -> documento, lector);
                
                if (retorno != DeserializationError::Ok) {
                    LOG("ERROR: Deserializar el MessagePack de la EEPROM falló con el error %d", retorno);
                    this -> estaCorrupta = true;
                    
                    return;
                }
                
                if (!(this -> documento.template is<JsonObject>())) {
                    FLOGS("ADVERTENCIA: Reiniciando documento leído porque no es un objeto JSON");
                    this -> documento.clear();
                }
                
                size_t versionDocumento = this -> getValorSetteando(CLAVE_VERSION, 1);
                LOG("BaseDatosEEPROM::inicializar() - MessagePack deserializado correctamente, de versión = %d", versionDocumento);
                imprimir(this -> documento);
                
                if (versionDocumento >= (this -> version) || !(this -> migrador)) {
                    return;
                }
                
                this -> migrador -> notificar(this -> documento);
                this -> documento[CLAVE_VERSION] = (this -> version);
                this -> guardar();
            }
            
            size_t medirSerializado(void) {
                return measureMsgPack(this -> documento);
            }
            
            template <typename T>
            T getValor(const char *clave, Print *salida = nullptr) {
                GET_VALOR(clave, salida);
                return this -> documento[clave];
            }
            
            template <typename T>
            const T &getValor(const char *clave, Print *salida = nullptr) const {
                GET_VALOR(clave, salida);
                return this -> documento[clave];
            }
            
            template <typename T>
            bool setValor(const char *clave, const T valor, Print *salida = nullptr) {
                T copiaValor = valor;
                CLOG_PUNTERO_IMPRESORA(salida, "Escribiendo BaseDatosEEPROM::setValor('", clave, "', ", valor, ')');
                SET_VALOR(clave, copiaValor, CAPACIDAD_STRINGS, salida);
            }
            
            bool setValor(const char *clave, const char *valor, Print *salida = nullptr) {
                StringEstatica<CAPACIDAD_STRINGS> copiaValor(valor);
                CLOG_PUNTERO_IMPRESORA(salida, "Escribiendo BaseDatosEEPROM::setValor('", clave, "', '", valor, "')");
                SET_VALOR(clave, copiaValor.getContenido(), CAPACIDAD_STRINGS, salida);
            }
            
            template <typename T>
            const T getValorSetteando(const char *clave, const T valorPredeterminado, Print *salida = nullptr) const {
                GET_VALOR_SETTEANDO(clave, valorPredeterminado, salida);
                return this -> documento[clave];
            }
            
            template <typename T>
            T getValorSetteando(const char *clave, T valorPredeterminado, Print *salida = nullptr) {
                GET_VALOR_SETTEANDO(clave, valorPredeterminado, salida);
                return this -> documento[clave];
            }
            
            bool guardar(Print *salida = nullptr) {
                if (this -> estaCorrupta) {
                    CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se accedió a BaseDatosEEPROM::guardar() con la BD corrupta");
                    return false;
                }
                
                //EscritorEEPROM escritor(DIRECCION_DOCUMENTO, this -> eeprom);
                CLOG_PUNTERO_IMPRESORA(salida, "DIRECCION_DOCUMENTO =", DIRECCION_DOCUMENTO, "this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1 =", this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1);
                EepromStream escritor(DIRECCION_DOCUMENTO, this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1);
                size_t tamanioEscrito = serializeMsgPack(this -> documento, escritor);
                
                this -> eeprom -> put(DIRECCION_NUM_BYTES, tamanioEscrito);
                escritor.flush();
                
                StaticJsonDocument<CAPACIDAD_JSON> documentoReleido;
                size_t numBytesUsadosReleido;
                this -> eeprom -> get(DIRECCION_NUM_BYTES, numBytesUsadosReleido);
                
                CLOG_PUNTERO_IMPRESORA(salida, "BaseDatosEEPROM::guardar() - numBytesUsadosReleido =", numBytesUsadosReleido);
                
                if (numBytesUsadosReleido > (this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1)) {
                    LOG("ERROR: La cantidad de bytes releidos es mayor a la posible de almacenar en la EEPROM");
                    this -> estaCorrupta = true;
                    
                    return false;
                }

                DeserializationError retorno = deserializeMsgPack(this -> documento, escritor);
                
                if (retorno != DeserializationError::Ok) {
                    CLOG_PUNTERO_IMPRESORA(salida, "ERROR: Re-deserializar el MessagePack de la EEPROM falló con el error", retorno.c_str());
                    this -> estaCorrupta = true;
                    
                    return false;
                }
                
                if (!(this -> documento.template is<JsonObject>())) {
                    CLOG_PUNTERO_IMPRESORA(salida, "ERROR: El documento releido no es un objeto JSON");
                    this -> estaCorrupta = true;
                    
                    return false;
                }
                
                CLOG_PUNTERO_IMPRESORA(salida, "BaseDatosEEPROM::guardar() - Guardados", tamanioEscrito, '/', this -> eeprom -> length(), "bytes correctamente");
                return true;
            }
            
            template <typename T_VALOR>
            bool contieneClave(const char *ingr) {
                return (this -> documento.containsKey(ingr)) && (this -> documento[ingr].template is<T_VALOR>());
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "BaseDatosEEPROM", leerAlInicializar, estaCorrupta, version, migrador)
                    + impresora.println()
                    + serializeJsonPretty(this -> documento, impresora);
            }
    };
#endif

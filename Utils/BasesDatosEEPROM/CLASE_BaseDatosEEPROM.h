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

#define GET_VALOR(clave) \
    if (this -> estaCorrupta) { \
        LOG("ADVERTENCIA: Se ejecutó BaseDatosEEPROM::getValor('%s') con la BD corrupta. Se retornará el valor indeterminado", clave); \
 \
        if (this -> documento.containsKey(clave)) { \
            FLOGS("ADVERTENCIA: Se retornará el valor previamente almacenado en esa clave."); \
        } \
        else { \
            FLOGS("ADVERTENCIA: Se retornará el valor predeterminado para ese tipo de datos."); \
        } \
    }

#define GET_VALOR_SETTEANDO(clave, valorPredeterminado) \
    if (this -> estaCorrupta) { \
        LOG("ADVERTENCIA: Se ejecutó BaseDatosEEPROM::getValorSetteando('%s') con la BD corrupta. Se retornará el valor predeterminado", clave); \
        return valorPredeterminado; \
    } \
 \
    if (!(this -> documento.containsKey(clave))) { \
        this -> setValor(clave, valorPredeterminado); \
    } \
 \
    if (this -> estaCorrupta) { \
        LOG("ADVERTENCIA: Se corrompió la BD tras ejecutar BaseDatosEEPROM::getValorSetteando('%s')", clave); \
 \
        if (!(this -> documento.containsKey(clave))) { \
            FLOGS("ADVERTENCIA: Se retornará el valor predeterminado"); \
            return valorPredeterminado; \
        } \
    }

#define SET_VALOR(clave, copiaValor, CAPACIDAD_STRINGS) \
    if (this -> estaCorrupta) { \
        LOG("ADVERTENCIA: Se accedió a BaseDatosEEPROM::setValor('%s') con la BD corrupta", clave); \
        return false; \
    } \
 \
    StringEstatica<CAPACIDAD_STRINGS> copiaClave(clave); \
 \
    LOG("Escribiendo BaseDatosEEPROM::setValor('%s') = %s", clave, copiaClave.getContenido()); \
    this -> documento.garbageCollect(); \
    this -> documento[copiaClave.getContenido()] = copiaValor; \
 \
    if (this -> documento.overflowed()) { \
        LOG("ERROR: Al intentar insertar la clave '%s', falló porque el StaticJsonDocument<%d> se llenó", clave, CAPACIDAD_JSON); \
        this -> estaCorrupta = true; \
        return false; \
    } \
 \
    size_t tamanioSerializado = this -> medirSerializado(); \
    size_t tamanioEEPROM = (this -> eeprom -> length() - DIRECCION_DOCUMENTO + 1); \
 \
    if (tamanioSerializado > tamanioEEPROM) { \
        LOG("ADVERTENCIA: Tras insertar la clave '%s', el documento serializado queda de tamaño %d y no entra en la EEPROM (de capacidad %d)", clave, tamanioSerializado, tamanioEEPROM); \
        this -> estaCorrupta = true; \
        return false; \
    } \
 \
    LOG("BaseDatosEEPROM::setValor('%s') finalizó correctamente", clave); \
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
                    LOG("ERROR: La cantidad de bytes leidos es mayor a la posible de almacenar en la EEPROM");
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
            T &getValor(const char *clave) {
                GET_VALOR(clave);
                return this -> documento[clave];
            }
            
            template <typename T>
            const T &getValor(const char *clave) const {
                GET_VALOR(clave);
                return this -> documento[clave];
            }
            
            template <typename T>
            bool setValor(const char *clave, const T valor) {
                T copiaValor = valor;
                SET_VALOR(clave, copiaValor, CAPACIDAD_STRINGS);
            }
            
            bool setValor(const char *clave, const char *valor) {
                StringEstatica<CAPACIDAD_STRINGS> copiaValor(valor);
                LOG("Escribiendo BaseDatosEEPROM::setValor('%s', '%s') = %s", clave, valor, copiaValor.getContenido()); \
                SET_VALOR(clave, copiaValor.getContenido(), CAPACIDAD_STRINGS);
            }
            
            template <typename T>
            const T getValorSetteando(const char *clave, const T valorPredeterminado) const {
                GET_VALOR_SETTEANDO(clave, valorPredeterminado);
                return this -> documento[clave];
            }
            
            template <typename T>
            T getValorSetteando(const char *clave, T valorPredeterminado) {
                GET_VALOR_SETTEANDO(clave, valorPredeterminado);
                return this -> documento[clave];
            }
            
            bool guardar(void) {
                if (this -> estaCorrupta) {
                    FLOGS("ADVERTENCIA: Se accedió a BaseDatosEEPROM::guardar() con la BD corrupta");
                    return false;
                }
                
                //EscritorEEPROM escritor(DIRECCION_DOCUMENTO, this -> eeprom);
                LOG("DIRECCION_DOCUMENTO = %d, this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1 = %d", DIRECCION_DOCUMENTO, this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1);
                EepromStream escritor(DIRECCION_DOCUMENTO, this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1);
                size_t tamanioEscrito = serializeMsgPack(this -> documento, escritor);
                
                this -> eeprom -> put(DIRECCION_NUM_BYTES, tamanioEscrito);
                escritor.flush();
                
                StaticJsonDocument<CAPACIDAD_JSON> documentoReleido;
                size_t numBytesUsadosReleido;
                this -> eeprom -> get(DIRECCION_NUM_BYTES, numBytesUsadosReleido);
                
                LOG("BaseDatosEEPROM::guardar() - numBytesUsadosReleido = %d", numBytesUsadosReleido);
                
                if (numBytesUsadosReleido > (this -> eeprom -> length() - DIRECCION_DOCUMENTO - 1)) {
                    LOG("ERROR: La cantidad de bytes releidos es mayor a la posible de almacenar en la EEPROM");
                    this -> estaCorrupta = true;
                    
                    return false;
                }

                DeserializationError retorno = deserializeMsgPack(this -> documento, escritor);
                
                if (retorno != DeserializationError::Ok) {
                    LOG("ERROR: Re-deserializar el MessagePack de la EEPROM falló con el error %d", retorno);
                    this -> estaCorrupta = true;
                    
                    return false;
                }
                
                if (!(this -> documento.template is<JsonObject>())) {
                    FLOGS("ERROR: El documento releido no es un objeto JSON");
                    this -> estaCorrupta = true;
                    
                    return false;
                }
                
                LOG("BaseDatosEEPROM::guardar() - Guardados %d/%d bytes correctamente", tamanioEscrito, this -> eeprom -> length());
                return true;
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

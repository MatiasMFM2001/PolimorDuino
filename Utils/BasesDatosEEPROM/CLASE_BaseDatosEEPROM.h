/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BASE_DATOS_EEPROM
#define BASE_DATOS_EEPROM

#define DIRECCION_NUM_BYTES (0)
#define DIRECCION_DOCUMENTO (DIRECCION_NUM_BYTES + sizeof(size_t))

#include <ArduinoJson.h>
#include "../FuncionesGlobales.h"
#include "CLASE_LectorEEPROM.h"
#include "CLASE_EscritorEEPROM.h"
#include <EEPROM.h>
    template <size_t CAPACIDAD_JSON, typename T_EEPROM = EEPROMClass>
    class BaseDatosEEPROM : public Inicializable {
        private:
            T_EEPROM *eeprom;
            StaticJsonDocument<CAPACIDAD_JSON> documento;
            bool leerAlInicializar;
            bool estaCorrupta;
            
        public:
            BaseDatosEEPROM(T_EEPROM *eeprom, bool leerAlInicializar = false)
                : eeprom(eeprom), documento(StaticJsonDocument<CAPACIDAD_JSON>()), leerAlInicializar(leerAlInicializar), estaCorrupta(false)
            {}
            
            void inicializar(void) override {
                if (!(this -> leerAlInicializar)) {
                    return;
                }
                
                size_t numBytesUsados;
                this -> eeprom -> get(DIRECCION_NUM_BYTES, numBytesUsados);
                
                LectorEEPROM lector(DIRECCION_DOCUMENTO, this -> eeprom, numBytesUsados);
                DeserializationError retorno = deserializeMsgPack(this -> documento, lector);
                
                if (retorno == DeserializationError::Ok) {
                    return;
                }
                
                LOG("ERROR: Deserializar el MessagePack de la EEPROM falló con el error %d", retorno);
                this -> estaCorrupta = true;
            }
            
            size_t medirSerializado(void) {
                return measureMsgPack(this -> documento);
            }
            
            template <typename T>
            const T getValorSetteando(const char *clave, const T valorPredeterminado) {
                if (this -> estaCorrupta) {
                    LOG("ADVERTENCIA: Se ejecutó BaseDatosEEPROM::getValorSetteando('%s') con la BD corrupta. Se retornará el valor predeterminado", clave);
                    return valorPredeterminado;
                }
                
                if (!(this -> documento.containsKey(clave))) {
                    this -> documento.garbageCollect();
                    this -> documento[clave] = valorPredeterminado;
                    
                    if (this -> documento.overflowed()) {
                        LOG("ERROR: Al intentar insertar la clave '%s', falló porque el StaticJsonDocument<%d> se llenó", clave, CAPACIDAD_JSON);
                        this -> estaCorrupta = true;
                    }
                    
                    size_t tamanioSerializado = this -> medirSerializado();
                    size_t tamanioEEPROM = (this -> eeprom -> length() - DIRECCION_DOCUMENTO + 1);
                    
                    if (tamanioSerializado > tamanioEEPROM) {
                        LOG("ADVERTENCIA: Tras insertar la clave '%s', el documento serializado queda de tamaño %d y no entra en la EEPROM (de capacidad %d)", clave, tamanioSerializado, tamanioEEPROM);
                        this -> estaCorrupta = true;
                    }
                }
                
                if (this -> estaCorrupta) {
                    LOG("ADVERTENCIA: Se corrompió la BD tras ejecutar BaseDatosEEPROM::getValorSetteando('%s')", clave);
                    
                    if (!(this -> documento.containsKey(clave))) {
                        FLOGS("ADVERTENCIA: Se retornará el valor predeterminado");
                        return valorPredeterminado;
                    }
                }
                
                return this -> documento[clave];
            }
            
            bool guardar(void) {
                if (this -> estaCorrupta) {
                    FLOGS("ADVERTENCIA: Se accedió a BaseDatosEEPROM::guardar() con la BD corrupta");
                    return false;
                }
                
                EscritorEEPROM escritor(DIRECCION_DOCUMENTO, this -> eeprom);
                size_t tamanioEscrito = serializeMsgPack(this -> documento, escritor);
                
                this -> eeprom -> put(DIRECCION_NUM_BYTES, tamanioEscrito);
                return true;
            }
    };
#endif

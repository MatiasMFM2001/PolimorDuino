/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INVOCADOR_CALLBACKS
#define INVOCADOR_CALLBACKS

#include "../../Callbacks/INTERFAZ_CallbackResultado.h"
#include "CLASE_Comando.h"
    template<size_t CAPACIDAD_COMANDOS, size_t CAPACIDAD_NOMBRE_COMANDOS, size_t CAPACIDAD_MENSAJE_ERROR_COMANDOS>
    class InvocadorCallbacks : public CallbackResultado<CanalBidireccional<JsonDocument, Print>> {
        private:
            Array<Comando<CAPACIDAD_NOMBRE_COMANDOS, CAPACIDAD_MENSAJE_ERROR_COMANDOS>, CAPACIDAD_COMANDOS> comandos;

        public:
            InvocadorCallbacks(Array<Comando<CAPACIDAD_NOMBRE_COMANDOS, CAPACIDAD_MENSAJE_ERROR_COMANDOS>, CAPACIDAD_COMANDOS> comandos)
                : comandos(comandos)
            {}
            
            InvocadorCallbacks(Comando<CAPACIDAD_NOMBRE_COMANDOS, CAPACIDAD_MENSAJE_ERROR_COMANDOS> comandos[CAPACIDAD_COMANDOS])
                : InvocadorCallbacks(Array<Comando<CAPACIDAD_NOMBRE_COMANDOS, CAPACIDAD_MENSAJE_ERROR_COMANDOS>, CAPACIDAD_COMANDOS>(comandos))
            {}

            void notificar(CanalBidireccional<JsonDocument, Print> &resultado) override {
                JsonDocument &documento = resultado.entrada;
                Print &salida = resultado.salida;

                const char *comando = documento[CLAVE_COMANDO];
                const char *nombreComando = (comando + 1);
                const JsonArray &argumentos = documento[CLAVE_ARGS];
                const size_t numArgs = argumentos.size();

                for (Comando<CAPACIDAD_NOMBRE_COMANDOS, CAPACIDAD_MENSAJE_ERROR_COMANDOS> &selec: this -> comandos) {
                    if (!selec.tieneNombre(nombreComando)) {
                        continue;
                    }
                    
                    if (selec.recibeNumArgumentos(numArgs)) {
                        selec.invocar(argumentos, numArgs, salida);
                    }
                    else {
                        CLOG_REFERENCIA_IMPRESORA(salida, "ERROR: Se esperaban entre", selec.getMinArgumentos(), 'y', selec.getMaxArgumentos(), "argumentos, pero se ingresaron", numArgs);
                    }
                    
                    return;
                }
                
                CLOG_REFERENCIA_IMPRESORA(salida, "ERROR: Comando inválido:", comando);
            }

            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "InvocadorCallbacks", comandos);
            }
    };
#endif

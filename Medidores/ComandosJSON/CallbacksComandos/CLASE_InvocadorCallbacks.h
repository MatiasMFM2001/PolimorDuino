/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INVOCADOR_CALLBACKS
#define INVOCADOR_CALLBACKS

#include "../../Callbacks/INTERFAZ_CallbackResultado.h"
#include "CLASE_Comando.h"
#include "../../../Utils/ValidadoresJSON/NodosPila/CLASE_NodoInicialPilaJSON.h"
    template<size_t CAPACIDAD_COMANDOS, size_t CAPACIDAD_NOMBRE_COMANDOS, size_t CAPACIDAD_PILA_JSON, size_t CAPACIDAD_MENSAJE_JSON>
    class InvocadorCallbacks : public CallbackResultado<CanalBidireccional<JsonDocument, Print>> {
        private:
            Array<Comando<CAPACIDAD_NOMBRE_COMANDOS>, CAPACIDAD_COMANDOS> comandos;

        public:
            InvocadorCallbacks(Array<Comando<CAPACIDAD_NOMBRE_COMANDOS>, CAPACIDAD_COMANDOS> comandos)
                : comandos(comandos)
            {}
            
            InvocadorCallbacks(const Comando<CAPACIDAD_NOMBRE_COMANDOS> comandos[CAPACIDAD_COMANDOS])
                : InvocadorCallbacks(Array<Comando<CAPACIDAD_NOMBRE_COMANDOS>, CAPACIDAD_COMANDOS>(comandos))
            {}

            void notificar(const CanalBidireccional<JsonDocument, Print> &resultado) override {
                JsonDocument &documento = resultado.entrada;
                Print &salida = resultado.salida;

                const char *comando = documento[CLAVE_COMANDO];
                const char *nombreComando = (comando + 1);
                const JsonArray &argumentos = documento[CLAVE_ARGS];
                const size_t numArgs = argumentos.size();

                for (Comando<CAPACIDAD_NOMBRE_COMANDOS> &selec: this -> comandos) {
                    if (!selec.tieneNombre(nombreComando)) {
                        continue;
                    }
                    
                    if (selec.recibeNumArgumentos(numArgs)) {
                        NodoInicialPilaJSON<CAPACIDAD_PILA_JSON, CAPACIDAD_MENSAJE_JSON> pilaClaves;
                        
                        if (selec.validarArgumentos(argumentos, pilaClaves)) {
                            selec.invocar(argumentos, numArgs, salida);
                        }
                        else {
                            CLOG_REFERENCIA_IMPRESORA(salida, F("ERROR: Se ingresó una cantidad válida de argumentos, pero alguno de ellos es inválido"));
                            pilaClaves.imprimirResultadoErroneo(salida, "argumentos");
                        }
                    }
                    else {
                        CLOG_REFERENCIA_IMPRESORA(salida, F("ERROR: Se esperaban entre"), selec.getMinArgumentos(), 'y', selec.getMaxArgumentos(), F("argumentos, pero se ingresaron"), numArgs);
                    }
                    
                    return;
                }
                
                CLOG_REFERENCIA_IMPRESORA(salida, F("ERROR: Comando inválido:"), comando);
                CLOG_REFERENCIA_IMPRESORA(salida, F("Los comandos disponibles son:"));
                
                for (Comando<CAPACIDAD_NOMBRE_COMANDOS> &selec: this -> comandos) {
                    CLOG_REFERENCIA_IMPRESORA(salida, '-', selec.getNombre().getContenidoConstante());
                }
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

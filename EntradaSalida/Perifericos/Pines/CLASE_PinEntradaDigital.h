/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PIN_ENTRADA_DIGITAL
#define PIN_ENTRADA_DIGITAL

#include "CLASE_Pin.h"
#include "../../Entradas/CLASE_EntradaDigital.h"

#ifdef __AVR__
    #include <PinChangeInterrupt.h>
#endif

#if !(defined(ARDUINO_ARCH_RP2040) && !defined(__MBED__))
    typedef void(*voidFuncPtr)(void);
    typedef byte PinStatus;
#endif
    /**
     * @brief Permite encapsular en un objeto, un pin de Entrada digital. Además,
     *  simplifica el uso de la librería de interrupciones por flanco.
     */
    template <byte MODO_PIN = INPUT>
    class PinEntradaDigital : public Pin<MODO_PIN>, public EntradaDigital {
        public:
            /**
             * @brief Construye un PinSalida, con el número de pin,
             *  configuración de inversión y estado inicial especificados.
             * 
             * @param numPin El número de pin especificado.
             * @param invertir @c true para invertir el funcionamiento,
             *  @c false para el caso contrario.
             * @param estadoInicial @c true para iniciar el programa con
             *  el pin encendido, @c false para el caso contrario.
             */
            PinEntradaDigital(pin_size_t numPin = -1, bool invertir = false)
                : Pin<MODO_PIN>(numPin, NUM_DIGITAL_PINS)
                , EntradaDigital(invertir)
            {}

            /**
             * @returns El valor leído del pin, sin invertir.
             */
            bool leerBajoNivel(void) override {
                return (this -> pinValido) && (digitalRead(this -> numPin) == HIGH);
            }
        
            /**
             * @returns El número identificatorio de interrupción por flancos,
             *  según el número de pin.
             */
            byte getNumPCINT(void) {
                return (this -> pinValido) ?
                    #ifdef __AVR__
                        digitalPinToPinChangeInterrupt(this -> numPin) : NOT_AN_INTERRUPT;
                    #else
                        digitalPinToInterrupt(this -> numPin) : -1;
                    #endif
            }
            
            /**
             * @brief Establece la función que será ejecutada cuando se detecte
             *  un flanco del tipo especificado (independientemente de la
             *  configuración de inversión).
             * 
             * @param funcion La función callback a ser ejecutada.
             * @param modo El modo de detección de flancos.
             */
            void vincularFuncionPCINT(voidFuncPtr funcion, PinStatus modo) {
                LOG("EJECUTANDO PinEntradaDigital::vincularFuncionPCINT(%d, %p, %d)", this -> numPin, funcion, modo);

                #ifdef __AVR__
                    attachPinChangeInterrupt
                #else
                    attachInterrupt
                #endif
                    (this -> getNumPCINT(), funcion, modo);
            }
            
            /**
             * @brief Desvincula la función establecida previamente, con las
             *  interrupciones por flanco emitidas por este pin.
             */
            void desvincularFuncionPCINT(void) {
                LOG("EJECUTANDO PinEntradaDigital::desvincularFuncionPCINT(%d)", this -> numPin);

                #ifdef __AVR__
                    detachPinChangeInterrupt
                #else
                    detachInterrupt
                #endif
                    (this -> getNumPCINT());
            }
            
            /**
             * @brief Permite que este pin emita interrupciones por flanco.
             */
            void habilitarInterrupcion(void) {
                LOG("EJECUTANDO PinEntradaDigital::habilitarInterrupcion(%d)", this -> numPin);

                #ifdef __AVR__
                    enablePinChangeInterrupt(this -> getNumPCINT());
                #else
                    FLOGS("ADVERTENCIA: En esta plataforma no hacía falta invocar a este método");
                #endif
            }
            
            /**
             * @brief Deniega que este pin emita interrupciones por flanco.
             */
            void deshabilitarInterrupcion(void) {
                LOG("EJECUTANDO PinEntradaDigital::deshabilitarInterrupcion(%d)", this -> numPin);

                #ifdef __AVR__
                    disablePinChangeInterrupt(this -> getNumPCINT());
                #else
                    FLOGS("ADVERTENCIA: En esta plataforma no hacía falta invocar a este método");
                #endif
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "PinEntradaDigital") + SUPERCLASES_A_JSON(impresora, Pin<MODO_PIN>, EntradaDigital);
            }
    };
#endif

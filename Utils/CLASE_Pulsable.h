/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PULSABLE
#define PULSABLE

#include <Printable.h>
#include <Print.h>
    /**
     * @brief Define métodos para los objetos que puedan ser encendidos y
     *  apagados, los cuales DEBEN sobreescribir o @c setEstado(), o
     *  @c encender() y @c apagar() para evitar una recursión infinita.
     */
    class Pulsable : virtual public Printable {
        private:
            /** @brief El estado actual del objeto. */
            bool estadoActual;
        
        protected:
            /**
             * @brief Establece el valor de la variable de instancia
             *  @c estadoActual.
             *
             * @param valor El valor a asignar.
             */
            void setEstadoActual(bool valor);
        
        public:
            /**
             * @brief Construye un Pulsable, con el estado inicial especificado.
             * 
             * @param estadoInicial @c true para iniciar el programa con
             *  el objeto encendido, @c false para el caso contrario.
             */
            Pulsable(bool estadoInicial, bool settearEstado = true);
            
            /**
             * @brief Pone al objeto en estado "Encendido".
             */
            virtual void encender(void);
            
            /**
             * @brief Pone al objeto en estado "Apagado".
             */
            virtual void apagar(void);
            
            /**
             * @brief Establece el estado actual del objeto al especificado.
             * 
             * @param valor @c true para encenderlo, @c false para el caso
             *  contrario.
             */
            virtual void setEstado(bool valor);
            
            /**
             * @returns El estado actual del objeto.
             */
            bool getEstado(void);
            
            /**
             * @brief Pone al objeto en el estado opuesto al actual.
             */
            void invertirEstado(void);

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override;
    };
#endif

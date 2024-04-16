#ifndef INVERSOR_PULSABLE
#define INVERSOR_PULSABLE

#include "CLASE_Pulsable.h"
    /**
     * @brief Decorador que permite invertir el funcionamiento del Pulsable
     *  decorado.
     */
    class InversorPulsable : public Pulsable {
        private:
            /** @brief Puntero al objeto decorado. */
            Pulsable *decorado;

        public:
            /**
             * @brief Construye un Pulsable, con el estado inicial especificado.
             *
             * @param estadoInicial @c true para iniciar el programa con
             *  el objeto decorado encendido, @c false para el caso contrario.
             */
            InversorPulsable(bool estadoInicial, Pulsable *decorado);

            /**
             * @brief Pone al objeto decorado en estado "Apagado".
             */
            void encender(void) override;

            /**
             * @brief Pone al objeto decorado en estado "Encendido".
             */
            void apagar(void) override;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override;
    };
#endif

#ifndef PULSABLE
#define PULSABLE

#include <Printable.h>
	/**
	 * @brief Define métodos para los objetos que puedan ser encendidos y
	 *  apagados, los cuales DEBEN sobreescribir o @code setEstado(), o
     *  @code encender() y @code apagar() para evitar una recursión infinita.
	 */
    class Pulsable : virtual public Printable {
        private:
            bool estadoActual;
        
        protected:
            void setEstadoActual(bool valor);
        
        public:
            /**
             * @brief Construye un Pulsable, con el estado inicial especificado.
             * 
             * @param estadoInicial @code true para iniciar el programa con
             *  el objeto encendido, @code false para el caso contrario.
             */
            Pulsable(bool estadoInicial, bool settearEstado = true);
            
            /**
             * @brief Pone al objeto en estado "Encendido".
             */
            virtual void encender();
            
            /**
             * @brief Pone al objeto en estado "Apagado".
             */
            virtual void apagar();
            
            /**
             * @brief Establece el estado actual del objeto al especificado.
             * 
             * @param valor @code true para encenderlo, @code false para el caso
             *  contrario.
             */
            virtual void setEstado(bool valor);
            
            bool getEstado();

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print& impresora) const override;
    };
#endif

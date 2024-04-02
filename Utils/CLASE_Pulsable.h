#ifndef PULSABLE
#define PULSABLE

#include <Printable.h>
	/**
	 * @brief Define métodos para los objetos que puedan ser encendidos y
	 *  apagados, los cuales DEBEN sobreescribir o @code setEstado(), o
     *  @code encender() y @code apagar() para evitar una recursión infinita.
	 */
    class Pulsable : virtual public Printable {
        public:
            /**
             * @brief Construye un Pulsable, con el estado inicial especificado.
             * 
             * @param estadoInicial @code true para iniciar el programa con
             *  el objeto encendido, @code false para el caso contrario.
             */
            Pulsable(bool estadoInicial);
            
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
    };
#endif

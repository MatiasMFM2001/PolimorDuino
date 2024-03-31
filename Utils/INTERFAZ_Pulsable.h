#ifndef PULSABLE
#define PULSABLE

#include <Printable.h>
	/**
	 * @brief Define una interfaz para los objetos que puedan ser encendidos y
	 *  apagados.
	 */
    class Pulsable : virtual public Printable {
        public:
            /**
             * @brief Pone al objeto en estado "Encendido".
             */
            virtual void encender() = 0;
            
            /**
             * @brief Pone al objeto en estado "Apagado".
             */
            virtual void apagar() = 0;
    };
#endif

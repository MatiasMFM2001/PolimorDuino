#ifndef WRAPPER_PUNTERO
#define WRAPPER_PUNTERO

#include <Printable.h>
#define NULLPTR_TO_STRING "null"
    /**
     * @brief Encapsula un puntero crudo, permitiendo imprimirlo.
     * 
     * @tparam TTipoDato El tipo de dato a apuntar.
     */
    template <typename TTipoDato>
    class WrapperPuntero : public Printable {
        private:
            /** @brief Puntero al dato. */
            TTipoDato* puntero;
        
        public:
            /**
             * @brief Construye un WrapperPuntero, con el puntero especificado.
             * 
             * @param puntero El puntero especificado.
             */
            WrapperPuntero(TTipoDato* puntero = nullptr)
                : puntero(puntero)
            {}
            
            
            /**
             * @returns El puntero encapsulado.
             */
            TTipoDato* getPuntero() const {
                return (this -> puntero);
            }
            
            /**
             * @returns La referencia al dato apuntado por el puntero
             *  encapsulado.
             */
            TTipoDato& getDato() const {
                return *(this -> puntero);
            }
            
            /**
             * @returns @code true si el puntero es nulo, @code false en caso
             *  contrario.
             */
            bool esNulo() const {
                return ((this -> puntero) == nullptr);
            }
        
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             * 
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print& impresora) const override {
                if (this -> esNulo()) {
                    return impresora.print(NULLPTR_TO_STRING);
                }
                
                return impresora.print(this -> getDato());
            }
            
            
            /**
             * @returns El puntero encapsulado.
             */
            operator TTipoDato*() const {
                return (this -> puntero);
            }
            
            /*operator TTipoDato&() const {
                return *(this -> puntero);
            }*/
    };
#endif

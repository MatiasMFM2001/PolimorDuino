#ifndef WRAPPER_PUNTERO
#define WRAPPER_PUNTERO

#include <Printable.h>
#include "FuncionesJSON.h"
    /**
     * @brief Encapsula un puntero crudo, permitiendo imprimirlo.
     *
     * @tparam T El tipo de dato a apuntar.
     */
    template <typename T>
    class WrapperPuntero : public Printable {
        private:
            /** @brief Puntero al dato. */
            T *puntero;

        public:
            /**
             * @brief Construye un WrapperPuntero, con el puntero especificado.
             *
             * @param puntero El puntero especificado.
             */
            WrapperPuntero(T *puntero = nullptr)
                : puntero(puntero)
            {}
            
            
            /**
             * @returns El puntero encapsulado.
             */
            T *getPuntero(void) const {
                return (this -> puntero);
            }
            
            /**
             * @returns La referencia al dato apuntado por el puntero
             *  encapsulado.
             */
            T &getDato(void) const {
                return *(this -> puntero);
            }
            
            /**
             * @returns @code true si el puntero es nulo, @code false en caso
             *  contrario.
             */
            bool esNulo(void) const {
                return ((this -> puntero) == nullptr);
            }
        
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                if (this -> esNulo()) {
                    return impresora.print(JSON_NULL);
                }
                
                return imprimirDatoJSON(impresora, this -> getDato());
            }
            
            
            /**
             * @returns El puntero encapsulado.
             */
            operator T*(void) const {
                return (this -> puntero);
            }
            
            /*operator T&(void) const {
                return *(this -> puntero);
            }*/
    };
#endif

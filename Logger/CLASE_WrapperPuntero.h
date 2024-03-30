#ifndef WRAPPER_PUNTERO
#define WRAPPER_PUNTERO

#include <Printable.h>
#include "FuncionesJSON.h"
    template <typename TTipoDato>
    class WrapperPuntero : public Printable {
        private:
            TTipoDato* puntero;
        
        public:
            WrapperPuntero(TTipoDato* puntero = nullptr)
                : puntero(puntero)
            {}
            
            
            
            TTipoDato* getPuntero() const {
                return (this -> puntero);
            }
            
            TTipoDato& getDato() const {
                return *(this -> puntero);
            }
            
            bool esNulo() const {
                return ((this -> puntero) == nullptr);
            }
        
            size_t printTo(Print& impresora) const override {
                if (this -> esNulo()) {
                    return impresora.print(JSON_NULL);
                }
                
                return impresora.print(this -> getDato());
            }
            
            
            
            operator TTipoDato*() const {
                return (this -> puntero);
            }
            
            /*operator TTipoDato&() const {
                return *(this -> puntero);
            }*/
    };
#endif
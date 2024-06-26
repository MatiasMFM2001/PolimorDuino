/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef WRAPPER_PUNTERO
#define WRAPPER_PUNTERO
    /**
     * @brief Encapsula un puntero crudo.
     *
     * @tparam T El tipo de dato a apuntar.
     */
    template <typename T>
    class WrapperPuntero {
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
             * @returns @c true si el puntero es nulo, @c false en caso
             *  contrario.
             */
            bool esNulo(void) const {
                return ((this -> puntero) == nullptr);
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

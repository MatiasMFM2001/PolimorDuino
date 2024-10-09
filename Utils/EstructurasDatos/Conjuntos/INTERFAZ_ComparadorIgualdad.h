/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef COMPARADOR_IGUALDAD
#define COMPARADOR_IGUALDAD
    template <typename T>
    class ComparadorIgualdad {
        public:
            virtual bool sonIguales(const T &valor1, const T &valor2) = 0;
    };
#endif

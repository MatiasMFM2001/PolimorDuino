/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#define TERNARIO_SIN_BIFURACION(condition, true_expression, false_expression) \
	((condition) * (true_expression) + !(condition) * (false_expression))

#define MAX_SIN_BIFURACION(value1, value2) TERNARIO_SIN_BIFURACION((value1 > value2), value1, value2)
#define MIN_SIN_BIFURACION(value1, value2) TERNARIO_SIN_BIFURACION((value1 < value2), value1, value2)

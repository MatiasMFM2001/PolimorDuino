/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUSION_TASK_SCHEDULER
#define INCLUSION_TASK_SCHEDULER

#ifdef INC_FREERTOS_H
    #define _TASK_THREAD_SAFE
#endif

#define _TASK_OO_CALLBACKS
#include <TaskScheduler.h>

#endif

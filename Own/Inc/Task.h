#ifndef __TASK_H
#define __TASK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cmsis_os2.h"

void ServosTask(void* argument);
void DetectTask(void* argument);
void ButtonTask(void* argument);

#ifdef __cplusplus
}
#endif

#endif
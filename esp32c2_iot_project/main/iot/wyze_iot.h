#ifndef WYZE_IOT_H
#define WYZE_IOT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "wyze-iot/wyze-iot-base.h"
#include "wyze-iot/wyze-iot-v3.h"
#include "wyze-iot/wyze-keep-alive.h"

int wyze_iot(void);

#ifdef __cplusplus
}
#endif
#endif
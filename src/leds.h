#include <stdint.h>
#include "errores.h"

#define bool uint16_t
#define TRUE 1
#define FALSE 0


void LedsCreate(uint16_t *puerto, logger_t logger);

void LedsOn(int led);

void LedsOff(int LED);

void LedsAllOn(void);

void LedsAllOff(void);

bool LedState(int led);

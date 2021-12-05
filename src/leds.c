#include "leds.h"

#define LEDS_INIT_STATE 0x0000
#define LEDS_ALLON      0xFFFF
#define LED_OFFSET     1
#define LED_ON_STATE   1
#define MASK_LED(x) (LED_ON_STATE << (x - LED_OFFSET))

static uint16_t *puerto;
static logger_t RegistrarError;

void LedsCreate(uint16_t *direccion, logger_t logger) {
    puerto = direccion;
    RegistrarError = logger;
    *puerto = LEDS_INIT_STATE;
}

void LedsOn(int led) {
    if ((led >= 1) && (led <= 16)) {
        *puerto |= MASK_LED(led);
    }
    else {
        RegistrarError(0, __FUNCTION__, __LINE__, "Numero de led invalido");
    }
}

void LedsOff(int led) {
    if ((led >= 1) && (led <= 16)) {
        *puerto &= ~MASK_LED(led);
    }
    else {
        RegistrarError(0, __FUNCTION__, __LINE__, "Numero de led invalido");
    }
}

void LedsAllOn(void) {
    *puerto = LEDS_ALLON;
}

void LedsAllOff(void) {
    *puerto = LEDS_INIT_STATE;
}

bool LedState(int led) {
    uint16_t value = FALSE;

    if ((led >= 1) && (led <= 16)) {
        if (*puerto & MASK_LED(led)) {
            value = TRUE;
        }
    }
    else {
        RegistrarError(0, __FUNCTION__, __LINE__, "Numero de led invalido");
    }

    return value;
}

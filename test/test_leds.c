/*
 * Despues de la configuración todos los leds deben quedar apagados
 * Prender un led cualquiera
 * Apagar un led cualquiera
 * Prender y apagar algunos leds
 * Preender todos los leds juntos
 * Apagar todos los leds juntos
 * Consultar el estado de un led apagado
 * Consultar el estado de un led encendido
 * Revisar los valores limites de los parámetros
 * Probar valores inválidos para los parámentros
 */

#include "unity.h"
#include "leds.h"
#include <string.h>

#define  LED            3
#define  LED_INFERIOR   1
#define  LED_SUPERIOR   16
#define  LED_OFFSET     1
#define  LED_ON_STATE   1
#define  LED_OFF_STATE  0
#define  LED_BIT(x)     (LED_ON_STATE << (x - LED_OFFSET))


static uint16_t puertoVirtual;

static struct {
    int gravedad;
    char funcion[64];
} error;


void RegistrarError(int gravedad, const char *funcion, int linea, const char *mensaje) {
    error.gravedad = gravedad;
    strcpy(error.funcion, funcion);
}

void setUp(void) {
    error.gravedad = -1;
    memset(error.funcion, 0, sizeof(error.funcion));
    LedsCreate(&puertoVirtual, RegistrarError);
}

// Despues de la configuración todos los leds deben quedar apagados
void test_todos_los_leds_apagados(void) {
    uint16_t puertoVirtual = 0xFFFF;
    LedsCreate(&puertoVirtual, RegistrarError);
    TEST_ASSERT_EQUAL_HEX16(0X0000, puertoVirtual);
}

// Prender un led cualquiera
void test_prender_un_led(void) {
    LedsOn(LED);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED), puertoVirtual);
}

//Apagar un led cualquiera
void test_apagar_un_led(void) {
    LedsOn(LED);
    LedsOff(LED);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

// Prender y apagar algunos leds
void test_prender_y_apagar_varios_leds(void) {
    LedsOn(LED);
    LedsOn(LED + 3);
    LedsOff(LED);

    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED + 3), puertoVirtual);
}

// Preender todos los leds juntos
void test_prender_todos_los_leds(void) {
    setUp();
    LedsAllOn();

    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puertoVirtual);
}

//Apagar todos los leds juntos
void test_apagar_todos_los_leds(void) {
    setUp();
    LedsAllOn();
    LedsAllOff();

    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

//Consultar el estado de un led apagado
void test_consultar_led_apagado(void) {
    setUp();
    bool state = 1;
    state = LedState(LED);
    TEST_ASSERT_EQUAL(LED_OFF_STATE, state);
}

//Consultar el estado de un led apagado
void test_consultar_led_encendido(void) {
    setUp();
    LedsOn(LED);
    bool state = 0;
    state = LedState(LED);
    TEST_ASSERT_EQUAL(LED_ON_STATE, state);
}

//Revisar estado de extremo superior
void test_valor_superior(void) {
    setUp();
    LedsOn(LED_SUPERIOR);
    bool state = 0;
    state = LedState(LED_SUPERIOR);
    TEST_ASSERT_EQUAL(LED_ON_STATE, state);
}

//Revisar estado de extremo inferior
void test_valor_inferior(void) {
    setUp();
    LedsOn(LED_INFERIOR);
    bool state = 0;
    state = LedState(LED_INFERIOR);
    TEST_ASSERT_EQUAL(LED_ON_STATE, state);
}

//Probar valores inválidos para los parámetros
void test_error_en_parametros(void) {
    LedsOn(17);
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsOn", error.funcion);
}

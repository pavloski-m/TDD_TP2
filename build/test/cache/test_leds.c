#include "src/leds.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


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





void test_todos_los_leds_apagados(void) {

    uint16_t puertoVirtual = 0xFFFF;

    LedsCreate(&puertoVirtual, RegistrarError);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0X0000)), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_un_led(void) {

    LedsOn(3);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)(((1 << (3 - 1)))), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_HEX16);

}





void test_apagar_un_led(void) {

    LedsOn(3);

    LedsOff(3);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_y_apagar_varios_leds(void) {

    LedsOn(3);

    LedsOn(3 + 3);

    LedsOff(3);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)(((1 << (3 + 3 - 1)))), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_todos_los_leds(void) {

    setUp();

    LedsAllOn();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_HEX16);

}





void test_apagar_todos_los_leds(void) {

    setUp();

    LedsAllOn();

    LedsAllOff();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_HEX16);

}





void test_consultar_led_apagado(void) {

    setUp();

    uint16_t state = 1;

    state = LedState(3);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((state)), (

   ((void *)0)

   ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_INT);

}





void test_consultar_led_encendido(void) {

    setUp();

    LedsOn(3);

    uint16_t state = 0;

    state = LedState(3);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((state)), (

   ((void *)0)

   ), (UNITY_UINT)(106), UNITY_DISPLAY_STYLE_INT);

}





void test_valor_superior(void) {

    setUp();

    LedsOn(16);

    uint16_t state = 0;



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((state)), (

   ((void *)0)

   ), (UNITY_UINT)(115), UNITY_DISPLAY_STYLE_INT);

}



void test_valor_inferior(void) {

    setUp();

    LedsOn(1);

    uint16_t state = 0;

    state = LedState(1);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((state)), (

   ((void *)0)

   ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_INT);



}





void test_error_en_parametros(void) {

    LedsOn(17);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((error.gravedad)), (

   ((void *)0)

   ), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("LedsOn")), (const char*)((error.funcion)), (

   ((void *)0)

   ), (UNITY_UINT)(131));

}

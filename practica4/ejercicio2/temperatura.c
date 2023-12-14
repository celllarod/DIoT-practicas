#include "contiki.h"
#include <stdio.h> /* For printf() */
#include <string.h>
#include <stdbool.h>
#include "dev/leds.h"
#include "dev/button-hal.h"
#include "lib/sensors.h"
#include "common/temperature-sensor.h"
#include "sys/log.h"

/*---------------------------------------------------------------------------*/
PROCESS(p4_exc_1_timer_process, "p4_exc_1 timer_process #1");
PROCESS(p4_exc_1_tmp_process, "p4_exc_1 TMP process #2");
PROCESS(button_hal, "Button HAL proccess");
AUTOSTART_PROCESSES(&p4_exc_1_timer_process, &p4_exc_1_tmp_process, &button_hal);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(p4_exc_1_timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();
  
  while(1){
    //printf("Timer process\n");
    etimer_set(&timer, CLOCK_SECOND * 2);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
    process_poll(&p4_exc_1_tmp_process);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(button_hal, ev, data)
{
  static bool switch_activo = false;

  PROCESS_BEGIN();

  while(1) {

    PROCESS_YIELD();

    // Se pulsa boton
    if(ev == button_hal_press_event) {
      switch_activo = !switch_activo;
      printf("switch:%d\n", switch_activo);
    }
  }

  PROCESS_END();
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(p4_exc_1_tmp_process, ev, data)
{
  static int16_t raw_tmp = 0;
  static int16_t int_tmp_c = 0;
  static int16_t frac_tmp_c = 0;
  static int16_t int_tmp_F = 0;
  static int16_t frac_tmp_F = 0;
  static int16_t tmp_F = 0;
  
  PROCESS_BEGIN();

  while(1){

    // Espera a que expire el timer
    PROCESS_WAIT_UNTIL(ev == PROCESS_EVENT_POLL);
    SENSORS_ACTIVATE(temperature_sensor);
    
    // Temperatura en grados Celcius
    raw_tmp = (int16_t)temperature_sensor.value(0);
    int_tmp_c = raw_tmp >> 2;
    frac_tmp_c = (raw_tmp & 0x3)*25;

    // Conversion de grados Celcius a Fahrenheit  
    tmp_F = raw_tmp * 2 + (32<<2);
    int_tmp_F = tmp_F >> 2;
    frac_tmp_F = (tmp_F & 0x3)*25;


    printf("temp_c:%d.%d;temp_f:%d.%d\n", int_tmp_c, frac_tmp_c, int_tmp_F, frac_tmp_F);

  }

  PROCESS_END();
}

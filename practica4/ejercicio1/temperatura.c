#include "contiki.h"
#include <stdio.h> /* For printf() */
#include <string.h>
#include "dev/leds.h"
#include "lib/sensors.h"
#include "common/temperature-sensor.h"


/*---------------------------------------------------------------------------*/
PROCESS(p4_exc_1_timer_process, "p4_exc_1 timer_process #1");
PROCESS(p4_exc_1_tmp_process, "p4_exc_1 TMP process #2");
AUTOSTART_PROCESSES(&p4_exc_1_timer_process, &p4_exc_1_tmp_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(p4_exc_1_timer_process, ev, data){
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

PROCESS_THREAD(p4_exc_1_tmp_process, ev, data){
  static int16_t raw_tmp = 0;
  static int16_t int_tmp_F = 0;
  static int16_t frac_tmp_F = 0;
  static int16_t tmp_F = 0;
  
  PROCESS_BEGIN();

  while(1){
    PROCESS_WAIT_EVENT();
    SENSORS_ACTIVATE(temperature_sensor);
    
    // Temperatura en grados Celsius
    raw_tmp = (int16_t)temperature_sensor.value(0);

    // Conversion de grados Celcius a Fahrenheit  
    tmp_F = raw_tmp * 2 + (32<<2); // <<2  para ajustar a la resolucon de 0.25 (1/4) de la temperatura medida (es quivalente a *4)
    int_tmp_F = tmp_F >> 2;
    frac_tmp_F = (tmp_F & 0x3)*25;

    printf("%d.%d\n", int_tmp_F, frac_tmp_F);

  }

  PROCESS_END();
}

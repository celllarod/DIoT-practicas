/**
 * \file
 *         Practica 1 Dispositivos IoT -> Ejercicio 5
 * \author
 *         celllarod
 */

#include "contiki.h"
#include <stdio.h> /* For printf() */
#include "os/lib/sensors.h"
#include "arch/platform/nrf52840/common/temperature-sensor.h"

/*---------------------------------------------------------------------------*/
PROCESS(temperature_sensor_process, "Lee el sensor de temperatura periodicamente");
PROCESS(timer_process, "Temporiza 3 segundos");


// Ambos procesos se ejecutaran desde el principio
AUTOSTART_PROCESSES(&temperature_sensor_process, &timer_process);

/*---------------------------------------------------------------------------
 * Proceso que lee la temperatura del sensor
 *--------------------------------------------------------------------------*/
PROCESS_THREAD(temperature_sensor_process, ev, data)
{
  PROCESS_BEGIN();

  while(1) {

     // Esperamos hasta recibir evento de timer_proccess
    PROCESS_WAIT_EVENT();

    // Activamos el sensor de temperatura
    SENSORS_ACTIVATE(temperature_sensor);

    // Leemos la temperatura del sensor 
    int16_t temp = temperature_sensor.value(0);
    

    // Desactivamos el sensor de temperatura
    SENSORS_DEACTIVATE(temperature_sensor);

    // Imprimimos la temperatura con 2 decimales teniendo en cuenta que es un entero y que la resolucion es de 0.25 haciendo cast a float
    // Dividimos entre 4 porque la resolucion del sensor es de 0.25 (1/4)
    printf("[temperature_sensor_process] Temperatura leída: %d.%d ºC\n", temp/4, temp%4*25);
    
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------
* Proceso que temporiza 3 segundos periodicamente y envia evento 
*---------------------------------------------------------------------------*/
PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  // Configuramos el timer periodico para que expire en 3 segundos.
  etimer_set(&timer, CLOCK_SECOND * 3);


  while(1) {

    // Esperamos a que expire el timer periodico y luego lo reseteamos.
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
    process_poll(&temperature_sensor_process);
  } 

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

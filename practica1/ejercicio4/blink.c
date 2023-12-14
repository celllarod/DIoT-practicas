/**
 * \file
 *         Practica 1 Dispositivos IoT -> Ejercicio 4
 * \author
 *         celllarod
 */

#include "contiki.h"
#include <stdio.h> /* For printf() */
#include "dev/leds.h"
/*---------------------------------------------------------------------------*/
PROCESS(parpadeo_1_process, "Conmuta Led1");
PROCESS(parpadeo_2_process, "Conmuta Led2");
PROCESS(timer_process, "Envia eventos");


// Ambos procesos se ejecutaran desde el principio
AUTOSTART_PROCESSES(&parpadeo_1_process, &parpadeo_2_process, &timer_process);

/*---------------------------------------------------------------------------
 * Proceso que se encarga de conmutar el estado del Led 1 cada 2 segundos. 
 * Este proceso permanecerá esperando un evento del proceso timer_process
 * antes de realizar la primera conmutación.
 *---------------------------------------------------------------------------*/
PROCESS_THREAD(parpadeo_1_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  // Esperamos hasta recibir evento de timer_proccess
  PROCESS_WAIT_EVENT();
  printf("[parpadeo_1_procces] Recibe evento de timer_process\n");

  // Configuramos el timer periodico para que expire en 2 segundos.
  etimer_set(&timer, CLOCK_SECOND * 2);

  while(1) {

    // Esperamos a que expire el timer periodico y luego lo reseteamos.
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);

    // Conmutamos el estado del Led1
    leds_single_toggle(LEDS_LED1);
    printf("[parpadeo_1_procces] LED1 conmuta\n");
    
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------
* Proceso que se encarga de conmutar el estado del Led 2 cada 3 segundos. 
* Este proceso permanecerá esperando un evento del proceso timer_process 
* antes de realizar la primera conmutación. 
*---------------------------------------------------------------------------*/
PROCESS_THREAD(parpadeo_2_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  // Esperamos hasta recibir evento de timer_proccess
  PROCESS_WAIT_EVENT();
  printf("[parpadeo_2_procces] Recibe evento de timer_process\n");

  // Configuramos el timer periodico para que expire en 3 segundos.
  etimer_set(&timer, CLOCK_SECOND * 3);


  while(1) {

    // Esperamos a que expire el timer periodico y luego lo reseteamos.
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);

    // Conmutamos el estado del Led1
    leds_single_toggle(LEDS_LED2);
    printf("[parpadeo_2_procces] LED2 conmuta\n");
  } 

  PROCESS_END();
}
/*---------------------------------------------------------------------------
* Proceso que gse ejecutará al inicio de la aplicación y tras esperar 5 
* segundos enviará un evento process_poll a Parpadeo_1 _process y 
* Parpadeo_2_process.
*---------------------------------------------------------------------------*/
PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  // Configuramos el timer periodico para que expire en 5 segundos.
  etimer_set(&timer, CLOCK_SECOND * 5);

  printf("[timer_procces] Esperando 5 segundos.\n");

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
  
  // Se genera evento hacia el proceso parpadeo_1_process y hacia parpadeo_2_process
  printf("[timer_procces] Envio de eventos\n");
  process_poll(&parpadeo_1_process);
  process_poll(&parpadeo_2_process);
 
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

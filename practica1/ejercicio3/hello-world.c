/**
 * \file
 *         Practica 1 Dispositivos IoT -> Ejercicio 3
 * \author
 *         celllarod
 */

#include "contiki.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
PROCESS(periodic_process, "Evento periodico process");

// Ambos procesos se ejecutaran desde el principio
AUTOSTART_PROCESSES(&periodic_process, &hello_world_process);

/*---------------------------------------------------------------------------
 * Proceso que se limitará a esperar eventospara imprimir un mensaje con un
 * contador que se incrementará en cada evento recibido. Este contador llegará
 * hasta 20, y posteriormente se reiniciará.
 *---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{

  static uint8_t contador = 0;

  PROCESS_BEGIN();

  while(1) {

    // Espero hasta recibir evento de periodic_process
    PROCESS_WAIT_EVENT();

    printf("Hello World! (number %u) \n", contador);

    // Incrementamos el contador. Si contador es 20 se resetea
    contador = (contador + 1) % 21;
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------
* Proceso que generará un evento cada 5 segundos y será enviado hacia el
* proceso hello_world_process utilizando la función process_poll.
*---------------------------------------------------------------------------*/
PROCESS_THREAD(periodic_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  // Configuramos el timer periodico para que expire en 5 segundos.
  etimer_set(&timer, CLOCK_SECOND * 5);

  while(1) {

    // Esperamos a que expire el timer periodico y luego lo reseteamos.
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);

    // Se genera evento hacia el proceso hello_world_process.
    process_poll(&hello_world_process);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

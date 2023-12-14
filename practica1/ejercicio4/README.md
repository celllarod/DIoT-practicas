## Ejercicio 4: Parpadeo de leds (3 Puntos) 
Realice la aplicación “Blink” que conmute los dos les de la placa cada 2 y 3 segundos respectivamente. Para ello se hará uso de 3 procesos/protohilos: 
- parpadeo_1_process: Se encarga de conmutar el estado del Led 1 cada 2 segundos. Este proceso permanecerá esperando un evento del proceso timer_process antes de realizar la primera conmutación. 
- parpadeo_2_process: Se encarga de conmutar el estado del Led 2 cada 3 segundos. Este proceso permanecerá esperando un evento del proceso timer_process antes de realizar la primera conmutación. 
- timer_process: Proceso que se ejecutará al inicio de la aplicación y tras esperar 5 segundos enviará un evento process_poll a Parpadeo_1 _process y Parpadeo_2_process.

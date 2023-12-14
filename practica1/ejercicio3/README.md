## Ejercicio 3: Hello World modificado (2 Puntos)
Realice una aplicación “Hello World” modificada de forma que ahora existan dos
procesos:
- El original hello_world_process, que sólo se limitará a esperar eventos
para imprimir un mensaje con un contador que se incrementará en cada
evento recibido. Este contador llegará hasta 20, y posteriormente se
reiniciará.
- Un nuevo proceso que se llamará periodic_process. Se ejecutará desde
el principio junto con el anterior. Generará un evento cada 5 segundos y
será enviado hacia el proceso hello_world_process utilizando la función
process_poll.

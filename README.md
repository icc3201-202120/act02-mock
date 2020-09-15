# Sincronización de Threads

**Nombre:**

## Primera parte: Completar una barrera

Una N-barrera es una primitiva de sincronización que permite esperar
hasta que N threads progresen en un programa hasta un cierto punto,
vale decir, hasta en donde se encuentra la barrera. Una vez que todos
los threads llegan a la barrera, pueden continuar ejecutando en forma
concurrente.

La N-barrera expone a los threads una operación llamada `waitinbarrier`,
y contiene un contador inicializado en cero, que aumenta cada vez que
un thread invoca dicha operación. Si el valor del contador es menor
a N, el thread que invoca la operación permanece dormido. Por el 
contrario, si el contador alcanza valor N, todos los threads que se 
encontraban durmiendo en la barrera despiertan y continúan su 
ejecución pasado la barrera, junto con el último thread que llamó a 
`waitinbarrier`.

Para realizar tu trabajo, cuentas con la implementación parcial de
una barrera en el archivo `barrier.c` de este código base. Además, 
puedes revisar la definición de la estructura (struct) barrier en 
`barrier.h`.

En `barrier.c` hay comentarios en `waitinbarrier` para ayudarte en tu
tarea. En particular, debes notar que la barrera debe ser reutilizable,
es decir, la cuenta de threads debe volver a cero una vez que todos
los threads han llegado a la barrera y despertado.

Para probar tu implementación, simplemente compila y ejecuta:

```sh
make clean && make
./main
```

En `main.c` se hace uso de la barrera en la función `part1`. Tres
threads creados en la función `main` llaman a `waitinbarrier` dos
veces en esta función. La segunda llamada es para probar si la
reutilización de la barrera funciona correctamente.

Evaluación:

* .5 punto por incrementar correctamente el contador de la barrera
* 1 punto por despertar a los procesos dormidos cuando el valor del 
contador llega a N, utilizando correctamente lock y variable de condición.
* 1 punto por renovar la barrera una vez que todos los threads dormidos
despiertan.

Consejos:

* Sigue atentamente los comentarios en código en `barrier.c`.
* Recuerda que la variable de condición tiene una operación `broadcast`
que permite a un thread despertar a todos los threads que se han
dormido esperando en ella.
* Puedes revisar el archivo `common_threads.h` para encontrar algunas
macros creadas para uso más conveniente de las funciones de la API
de threads POSIX. Estas funciones son las utilizadas en los ejemplos 
del libro OSTEP.

## Segunda Parte: Coordinación entre threads con una variable de condición

Para continuar con la segunda parte, debes descomentar la línea
de código que dice `part2(args);` al final de la función `part1` de `main.c`.

En la función `part2` cada uno de los tres threads que ejecutaron en `part1`
tiene un rol diferente. El thread 1 (se revisa el número de thread con
`args->num`), inicializa un arreglo con valores aleatorios. El thread 2
busca el menor valor en el arreglo, y el thread 3 el mayor valor. Debes
sincronizar los threads, de manera que el thread 1 termine de inicializar
el arreglo _antes_ que los threads 2 y 3 hagan sus respectivas tareas.

Para lo anterior, tienes a disposición:

* Variable de condición `args->pcond` y flag `args->pready` para que 
threads 2 y 3 puedan esperar a que el thread 1 termine.
* Lock `args->plock` para usar junto con la variable de condición.

Evaluación:

* .75 Thread 1 siempre ejecuta antes que threads 2 y 3.
* .75 Threads 2 y 3 se duermen y despiertan en la variable de condición
correctamente.




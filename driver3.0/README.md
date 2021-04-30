# Driver 3.0

Este tercer driver guarda estrecha relación con el driver 4.0. Lo llamaremos *Dots* pues que simplemente imprime puntos por cada lectura que se ejectua sobre el mismo y cada 10 lecturas, imprimirá un asterisco.

La idea detrás de Driver3.0 es desarrollar un controlador de caracteres. Si bien podría tratarse de un driver más complejo en cuanto a implementación, se limitaron bastantes funciones a fin de guardar cierta semejanza con el Driver4.0. 

## Compilación

Recordemos los pasos establecidos previamente para compilar el módulo:

`make`

Generará el archivo *dots.ko*, que es nuestro módulo a emplear.

Una vez terminado su empleo, podemos limpiar el directorio ejecutando

`make clean`

## Modo de Uso

Una vez compilado y generado nuestro módulo (*dots.ko*), ejecutamos lo siguiente:

`sudo insmod dots.ko`

Debemos tener privilegios de administrador para poder insertar el módulo en el kernel. Luego con

`dmesg | tail`

imprimos en consola los últimos registros del sistema. Deberíamos ver algo como lo siguiente

```
[244735.584120] Major = 235, Minor = 0 
[244735.584122] Kernel Module Inserted Succeddfully...
```

Observemos que esta vez se muestran dos valores: *Major: 235 y Minor: 0*. Estos valores corresponder a dos enteros empleados para poder identificar tanto el controlador como el dispositivo a controlar.
Una lectura más profunda al respecto se puede encontrar en [Char Devices](https://static.lwn.net/images/pdf/LDD3/ch03.pdf).

`sudo rmmod helloWorld.ko`

Con este comando, removemos el módulo del kernel.

`dmesg`

Nuevamente imprimimos los registros del sistema y deberíamos obtener algo como lo siguiente:

```
[244763.216396] Kernel Module Removed Successfully...
```

## Creación de un device

Insertar el módulo de kernel no es suficiente. Simplemente hemos ampliado la funcionalidad del mismo.

Sin embargo, aún necesitamos crear un dispositivo a interactuar con dicho módulo.

Si ejecutamos

```
ls /dev/ | grep dots
```

No obtendríamos nada como respuesta. Debemos previamente crear el nodo.

*Observación!*: En primer lugar, debemos averiguar el valor de *MAJOR* obtenido cuando se insertó el módulo en el kernel. En nuestro caso, el entero 235 que obtuvimos cuando el módulo fue instalado en el kernel. El mismo fue un valor asignado dinámicamente, por lo que puede variar.

Para asegurarse cuál es el valor obtenido, o bien se puede corrobar el mismo en los mensajes de registros generados al momento de insertar el módulo, o bien con el siguiente comando:

```
grep -w dots /proc/devices
```

Con lo cual deberíamos obtener una salida como la siguiente:

```
235 dots
```

Una vez con eso resuelto, podemos ejecutar el siguiente comando:

```
sudo mknod -m 666 /dev/dots c 235 0
```

Con esto ya tendríamos todo listo para probar nuestro driver.


## Probando el módulo

Basta ejecutar el siguiente comando 

```
head -c42 /dev/dots
```

con lo cual deberíamos obtener una salida como la siguiente:

```
.........*.........*.........*.........*..
```

que era lo esperado.

## Limpiando el desorden

A fin de poder remover todo lo creado, podemos empezar con el nodo creado.

```
sudo rm /dev/dots
```

Y por ultimo, removiendo el modulo.


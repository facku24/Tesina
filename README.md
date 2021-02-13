# Tesina

Este repositorio sirve como proyecto de tesina. La idea de la misma es la de comparar dos lenguajes de programación, C y Rust, en el desarrollo de drivers y analizar cómo los bugs comunes reportados en C, son solventados o no por Rust.

Por bug entiéndase aquellos problemas de "*memory unsafety*", donde se permite a los programadores introducir ciertos tipos de errores permitiendo que los mismos causen serios problemas de seguridad. 

Los errores más frecuentes reportados son aquellos relacionados con espacialidad y temporalidad.

El término *espacialidad*, se refiere acceso de posiciones de memoria incorrecto. Como por ejemplo, intentar acceder a un arreglo en posiciones inválidas.

El término *temporalidad* hace referencia al uso de memoria previamente liberada, ya sea para su acceso o un nuevo intento por liberarla.

## Entorno

Todos los drivers son compilados para Ubuntu 20.04 version del kernel xxx

Las pruebas son realizadas en una máquina virtual creada con la aplicación qemu.

## Driver 1.0

Este primer driver corresponde al clásico *Hello World*. Ha sido tomado como ejemplo de la [página Embetronix](https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-part-2-first-device-driver/). 

La idea detrás de Driver1.0 es comenzar con claro ejemplo de módulo de kernel. Para los fines de la tesina, no aporta nada más que un background sobre cómo desarrollar un módulo simple que al momento de ser insertado en el kernel imprima el mensaje *Hello Wolrd* y al ser removido *Good Bye, Cruel World*.

### Compilación

Los pasos para compilar el kernel son los siguientes:

> make

Generará el archivo helloWolrd.ko, que es nuestro módulo a emplear.

Si queremos, podemos limpiar el directorio, para ello ejecutamo 

> make clean

### Modo de Uso

Una vez compilado y generado nuestro módulo (*helloWorld.ko*), ejecutamos los siguientes:

> sudo insmod helloWorld.ko

Debemos tener privilegios de administrador para poder insertar el módulo en el kernel.

> dmesg

Con el comando `dmesg` imprimos en consola los logs del sistema. Deberíamos ver algo como lo siguiente

```
[16190.064086] helloWorld: loading out-of-tree module taints kernel.
[16190.064138] helloWorld: module verification failed: signature and/or required key missing - tainting kernel
[16190.064962] Hello World!
```

> sudo rmmmod helloWorld.ko

Con este comando, removemos el módulo del kernel.

> dmesg

Nuevamente imprimimos los logs del sistema y deberíamos obtener algo como lo siguiente:

```
[16190.064086] helloWorld: loading out-of-tree module taints kernel.
[16190.064138] helloWorld: module verification failed: signature and/or required key missing - tainting kernel
[16190.064962] Hello World!
[16195.596519] Good Bye, Cruel World!
```

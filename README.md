# Tesina

Este repositorio sirve como proyecto de tesina. La idea de la misma es la de comparar dos lenguajes de programación, C y Rust, en el desarrollo de drivers y analizar cómo los bugs comunes reportados en C, son solventados o no por Rust.

Por bug entiéndase aquellos problemas de "*memory unsafety*", donde se permite a los programadores introducir ciertos tipos de errores permitiendo que los mismos causen serios problemas de seguridad. 

Los errores más frecuentes reportados son aquellos relacionados con espacialidad y temporalidad.

El término *espacialidad*, se refiere acceso de posiciones de memoria incorrecto. Como por ejemplo, intentar acceder a un arreglo en posiciones inválidas.

El término *temporalidad* hace referencia al uso de memoria previamente liberada, ya sea para su acceso o un nuevo intento por liberarla.

## Entorno

Todos los drivers son compilados para Ubuntu 20.04 version del kernel xxx

Las pruebas son realizadas en una máquina virtual creada con la aplicación qemu.

### Ejemplos

Cada uno de los directorios, consta de su propio `README.md` que establece el seteo previo del environment para poder ejectuarlo.
# Linux kernel modules in safe Rust

Este ejemplo es un driver simple en Rust. Al igual que `Driver1.0` simplemente imprime `Hello kernel module!` en stdout cuando es insertado en el kernel y, `My message is on the heap` y `Goodbye kernel module!` cuando es removido.

## Diseño

Ejecutamos [bindgen](https://github.com/rust-lang/rust-bindgen) en los headers del kernel para generar links automáticos de Rust FFI. Bindgen funciona con [Clang](https://clang.llvm.org), por lo que usamos el propio sistema de compilación del kernel para determinar los CFLAGS adecuados. Luego escribimos links seguros para estos tipos (vease los archivos dentro de `src /`).

Cada módulo del kernel en Rust vive en una caja `staticlib`, que genera un archivo `.a`. Pasamos este objeto al sistema de compilación de módulos del propio kernel de Linux para vincularlo a un `.ko`.

El kernel es intrínsecamente multiproceso: se puede acceder a los recursos del kernel desde múltiples procesos del espacio de usuario a la vez, lo que provoca que múltiples subprocesos de ejecución dentro del kernel manejen las llamadas al sistema (o interrupciones). Por lo tanto, el tipo `KernelModule` es [` Sync`](https://doc.rust-lang.org/book/ch16-04-extensible-concurrency-sync-and-send.html), por lo que todos los datos compartidos por un módulo del kernel debe ser seguro para acceder simultáneamente (por ejemplo, mediante la implementación del bloqueo).

## Requerimientos de sistema

Este proyecto se corre sobre Linux 5.8.0-43-generic (Ubuntu 20.04.2 LTS)

Necesitamos tener instalado [Rust](https://www.rust-lang.org) - en particular
Rust nightly, debido a que se emplea [algunos features inestables](https://github.com/fishinabarrel/linux-kernel-module-rust/issues/41) - y [Clang](https://clang.llvm.org). Vamos a necesitar LLVM/Clang 9 (released September 2019) o superior por múltiples razones, ante todo
[support for `asm goto`][]. Si usamos Debian, Ubuntu o un derivado, https://apt.llvm.org es genial.

Si el binario `clang` es demasiado antiguo, asegúrese de establecer la variable de entorno` CC` o `CLANG` adecuadamente, por ejemplo, `CC = clang-9`.

Kernles muy recientes pueden requerir versiones más recientes de Clang; pruebe Clang 11 si las versiones anteriores no le funcionan.

[#112]: https://github.com/fishinabarrel/linux-kernel-module-rust/issues/112
[support for `asm goto`]: https://github.com/fishinabarrel/linux-kernel-module-rust/issues/123

## Construyendo un modulo hello-world

1. Instalar clang, los headers de kernel, y los componentes `rust-src` `rustfmt` de `rustup`:

```
- sudo apt updata && apt-get install llvm clang clang-11 linux-headers-"$(uname -r)" # o el equivalente para tu SO
- snap install rustup --classic
- rustup toolchain install nightly
- apt install llvm-dev libclang-deb
- rustup component add --toolchain=nightly rust-src rustfmt
```

Observación: Puede ser útil instalar una versión en particular de la tool chain para el compilador.
En nuestro caso, la versión `1.53.0-nightly (5a4ab2645 2021-04-18)` presenta ciertas complicaciones al momento de compilar, por lo que debimos volver un release previo `rustc 1.52.0-nightly (3f5aee2d5 2021-02-12)`, el cual compila correctamente.

```
- rustup toolchain install nightly-2021-02-12
- rustup override set nightly-2021-02-12-x86_64-unknown-linux-gnu
```

Estos dos pasos instalan la versión y la establecen como la toolchain para esa sesión de consola. Es probable que futuras sesiones requieran que sea establecidad nuevamente.

2. entrar a la carpeta hello-world 

```
cd hello-world
```

3. Construir el módulo del kernel usando el sistema de compilación del kernel de Linux (kbuild), esto invocará `cargo` para compilar el código Rust

```
make
```

Observación: La compilación puede presentar el siguiente mensaje de error:

```
.hello_world.rust.o.cmd: No such file or directory
```

Una forma de solventar el mismo, es creando uno.

```
touch .hello_world.rust.o.cmd
```


4. insertar, remover el módulo y controlar los mensajes

```
sudo insmod helloworld.ko
sudo rmmod helloworld
dmesg | tail
```


# Librería de Arduino para MPU-9250

Esta librería encapsula la librería original de [Sparkfun](https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library) con tal de ofrecer nuevos métodos que simplifiquen el desarrollo con la IMU MPU-9250 durante las clases de Robótica del Grado de Ingeniería Biomédica de la Universitat de Barcelona. De igual modo, siguen estando disponibles las funciones avanzadas que ofrece la librería original de [Sparkfun](https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library).

## Instalación

###  Método 1

- Descargar el repositorio en una carpeta local.
- Descomprimir los contenidos del archivo descargado en una carpeta con el mismo nombre que el archivo principal del proyecto de Arduino. En este caso, `roboticsub-imu`.
- Modificar el archivo `roboticsub-imu.ino` a conveniencia.

### Método 2

- Descargar el repositorio en una carpeta local.

- Descomprimir los contenidos del archivo descargado.

- Copiar la carpeta `src` en la carpeta que contiene nuestro proyecto de Arduino.

- Hacer el *include* pertinente en el *sketch* principal de Arduino:

  ```c++
  #include "src/RoboticsUB.h"
  ```

## Uso

A ser una expansión de la librería de Sparkfun, el uso es exactamente el mismo que el descrito en la [página oficial](https://learn.sparkfun.com/tutorials/9dof-razor-imu-m0-hookup-guide#using-the-mpu-9250-dmp-arduino-library). La única diferencia es que debemos de crear un objeto de tipo `IMU`.

```c++
IMU imu;
```

A continuación, se describen las funciones añadidas.

#### Install()

Inicia la comunicación con la IMU y configura sus registros.

```c++
imu.Install();
```

#### GetQuaternion()

Devuelve un puntero a un vector con el cuaternión dela orientación actual de la IMU. 

```c++
float * q;
q = imu.GetQuaternion();
```

Los elementos `0`, `1`, `2` y `3` del vector corresponden a los componentes `w`, `x`, `y` y `z` del cuaternión `q = w + xi + yj + zk`.

#### Otros

El pin de interrupciones `INT` del MPU-9250 está activado para su uso.

## Licencia

Copyright (c) Albert Álvarez Carulla. Todos los derechos reservados.

Licenciado bajo licencia [GNU GPLv3](./LICENSE).
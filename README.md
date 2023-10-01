# SISTEMA DE RIEGO AUTOMATIZADO CON IoT PARA HUERTA INTELIGENTE

**OPEN SOURCE DESARROLLADO POR:**

- DIEGO A. TRUJILLO
- CRISTIAN AGUDELO
- YOINER A. LEUDO
- MALENA HERNANDEZ
- YULIANA OSORIO
- ISABELLA TABORDA
- CAMILO RIVERO
- CESAR ACEVEDO

**ÚLTIMA ACTUALIZACIÓN:** 01 OCT 2023

[INGRESAR A LA PÁGINA WEB DEL PROYECTO](https://cristiangudelo63.wixsite.com/huertaiot)

## Construir el proyecto

1. Descargar `Code.ino` en tu explorador de archivos.
2. Descargar e instalar el IDE de Arduino [Descargar IDE](https://www.arduino.cc/en/software)
3. Abrir el archivo `Code.ino` en el IDE.
4. Descargar las bibliotecas `SPI.h` y `Ethernet.h` en el IDE de Arduino.
5. Cambiar en `Code.ino`, la CONFIGURACIÓN DE RED EN SKETCH DE ARDUINO.
6. Verificar la compilación del código.
7. Cargar el código en el Arduino.

## Notas del Autor

- El código de Arduino está realizado solo para funcionar en una LAN (Red de Área Local).
- La biblioteca `Ethernet.h`, es por si está utilizando un Shield Ethernet, para conectar por cable UTP Ethernet. Si está utilizando una tarjeta con red inalámbrica, requiere instalar la librería correspondiente, ya sea para el ESP32 u otro.
- Si desea que la página esté publicada en intenet. Por favor ingresa a este proyecto (que es la continuación del mismo): https://github.com/CristianAgudelo63/HuertaIoT-Client
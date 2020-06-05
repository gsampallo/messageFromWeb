![Image](https://raw.githubusercontent.com/gsampallo/messageFromWeb/master/views/image/home.jpg)

# Mensajes IoT desde la Web

Sencilla demostración sobre como enviar mensajes desde la web a un dispositivo IoT.

## Instalacion

Es necesario tener instalado [nodejs](https://nodejs.org/es/), junto con la libreria mqtt. Para instalar los complementos se ejecuta:
```
npm install
npm install mqtt --save
```

Finalmente para ejecutar la aplicacion: 
```
node app.js
```

## Parametros

Es necesario en app.js configurar la ip correcta del servidor broker, al igual que en mqttweb.ino (junto con los parametros de la red wifi).

## Utils

Existe un sencillo script en Python llamado mensajes.py que permite ver los mensajes publicados. Requiere tener instalado paho.mqtt

Se instala ejecutando desde la consola

```
pip install paho.mqtt
```
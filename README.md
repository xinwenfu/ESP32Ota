This project is from https://github.com/atomic14/ESP32Ota.

# Introduction

This project demonstrates how to use the Arduino Over The Air update system on an ESP32.
Click the image to watch the demo video.

[![Demo Video](https://img.youtube.com/vi/_bMsrxiyuHs/0.jpg)](https://www.youtube.com/watch?v=_bMsrxiyuHs)

# Setup

1. Open a terminal in Ubuntu. Type the following command to install networking tools for Ubuntu
```
sudo apt install net-tools
```
Now we can check the IP address of Ubuntu with the following command
```
sudo ifconfig
```

2. 
Update the file `wifi_credentials.h` with your SSID and PASSWORD.

```c
#define SSID "YOUR_SSID"
#define PASSWORD "YOUR_PASSWORD"
```

Now just compile and run the sketch.

The first install will need to over USB.

Once the sketch is running you can go to "Tools" -> "Ports" and you should find your ESP32 listed as "esp_test".

You can change the name of your device by changing this line of code:

```c
ArduinoOTA.setHostname("esp_test");
```

# OTA in pio
In pio, we need to specify the upload_protocol and upload_port, which is the ip address of the board. One example platformio.ini looks like the following. This example uses the Arduino library installed by Arduino IDE. But really pay attention to the last two lines.

```
; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_extra_dirs = ~/Documents/Arduino/libraries
monitor_speed = 115200

upload_protocol = espota
upload_port = 192.168.1.18
```

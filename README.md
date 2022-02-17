# OTA via BLE on ESP32

This project demonstrates how to use the Arduino Over The Air update system on an ESP32.


# Setup

1. Open a terminal in Ubuntu. Type the following command to install networking tools for Ubuntu
```
sudo apt install net-tools
```
Now we can check the IP address of Ubuntu with the following command
```
sudo ifconfig
```

2. Clone this GitHub project within a folder at the Ubuntu VM.

For example, the following commands in a terminal clone the GitHub project to ~/home/iot/Documents

```
cd ~/Documents
git clone https://github.com/xinwenfu/ota.git
```

3. Open VS Code and import this GitHub project, which is an Arduino project
   - Click the PlatformIO icon
   - Click QUICK ACCESS -> PIO Home -> Open
   - Click *Import Arduino Project*
   - Select a board: Espressif ESP32 Dev Module
   - Choose a directory with existing Arduino IDE project: Places -> iot -> Documents -> ota
   - Click the button *Import*

4. Update the file `wifi_credentials.h` with your SSID and PASSWORD.

```
#define SSID "YOUR_SSID"
#define PASSWORD "YOUR_PASSWORD"
```
# Flashing the board for the first time

5. Compile the project

6. Upload the firmware USB
   - First installation of the firmware will need to be over USB. The code is written with the functionality of OTA and it shall be flashed into the ESP32 board running and waiting for later OTA requests.
   - Press the BOOT button (IO0) of the ESP32 board if needed during uploading

7. The firmware blinks the blue LED on the board
   - The ESP32 board is ready for upgrading through OTA if the blue LED on the board blinks

8. Use the Serial Monitor to see the output from the ESP board firmware, which prints out the IP address of the board

# OTA

9. Change the code, e.g, the frequency of the LED light blinking so that we will upload the new firmware to the board

10. In platformio.ini, specify the upload_protocol and upload_port, which is the ip address of the board. One example platformio.ini looks like the following. Pay attention to the last two lines.
   - Optionally, unplug the micro USB cable from the computer and plug it into another USB port 

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
monitor_speed = 115200

upload_protocol = espota ; Upload via OTA. 
upload_port = 192.168.1.7 ; Change the IP to IP of the ESP32 board
```

9. Compile the project 
10. Upload the firmware via OTA. You shall see a different uploading process  from the uploading process via USB


Notes:

This project is based on https://github.com/atomic14/ESP32Ota.
Click the image to watch the original demo video with Arduino IDE.

[![Demo Video](https://img.youtube.com/vi/_bMsrxiyuHs/0.jpg)](https://www.youtube.com/watch?v=_bMsrxiyuHs)

In the Arduino IDE, once the sketch is running you can go to "Tools" -> "Ports" and you should find your ESP32 listed as "esp_test". You can change the name of your device by changing this line of code:
```
ArduinoOTA.setHostname("esp_test");
```


# OTA via WiFi on ESP32

This project demonstrates how to use the Over The Air (OTA) update system on an ESP32 board. It also shows the dange of OTA without security. If security is not considered for OTA, an adversary may inject a malicious firmware into a victim device through the OTA. For secure OTA through https, refer to [Get Started With Secure ESP32 OTA through HTTPS](https://github.com/PBearson/Get-Started-With-ESP32-OTA).


# Setup
1. [Optional] If not configured, configure Ubuntu VM to use the briadged adaptor

2. [Optional] If not installed, open a terminal in Ubuntu, and type the following command to install networking tools
```
sudo apt install net-tools
```
Now we can check the IP address of Ubuntu with the following command
```
sudo ifconfig
```

3. Clone this GitHub project within a folder at the Ubuntu VM.

For example, the following commands in a terminal delete the old ota folder and clone the GitHub project to /home/iot/Documents

```
cd ~/Documents                                  # change to the folder Documents within the home folder
rm -rf ota                                      # delete the old ota folder
git clone https://github.com/xinwenfu/ota.git   # clone the github repository
```
where # indicates the rest of the line is comment.

4. Open VS Code and import this GitHub project, which is an Arduino project
   - Click the PlatformIO icon
   - Click *QUICK ACCESS* -> *PIO Home* -> *Open*
   - Click *Import Arduino Project*
   - Select a board: *Espressif ESP32 Dev Module*
   - *Choose a directory with existing Arduino IDE project*: *Places* -> *iot* -> *Documents* -> *ota*
   - Click the button *Import*

# Flashing the board for the first time via micro USB

5. Update the file `wifi_credentials.h` with your SSID and PASSWORD.

```
#define SSID "YOUR_SSID"
#define PASSWORD "YOUR_PASSWORD"
```
6. Compile the project

7. Upload the firmware USB
   - First installation of the firmware will need to be over USB. The code is written with the functionality of OTA and it shall be flashed into the ESP32 board running and waiting for later OTA requests.
   - Press the BOOT button (IO0) of the ESP32 board if needed during uploading

8. The firmware blinks the blue LED on the board
   - The ESP32 board is ready for upgrading through OTA if the blue LED on the board blinks

9. Use the Serial Monitor to see the output from the ESP board firmware, which prints out the IP address of the board

# OTA via WiFi

10. Change the code, e.g, the frequency of the LED light blinking so that we will upload the new firmware to the board

11. In platformio.ini, specify the upload_protocol and upload_port, which is the ip address of the board. One example platformio.ini looks like the following. Pay attention to the last two lines.
    - Optionally, unplug the micro USB cable from the computer and plug it into another USB port. The purpose is to show we will not need upload the firmware via USB. 

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
10. Upload the firmware via OTA. You shall see a different uploading process from the uploading process via USB


Notes:

This project is based on https://github.com/atomic14/ESP32Ota.
Click the image to watch the original demo video with Arduino IDE.

[![Demo Video](https://img.youtube.com/vi/_bMsrxiyuHs/0.jpg)](https://www.youtube.com/watch?v=_bMsrxiyuHs)

In the Arduino IDE, once the sketch is running you can go to "Tools" -> "Ports" and you should find your ESP32 listed as "esp_test". You can change the name of your device by changing this line of code:
```
ArduinoOTA.setHostname("esp_test");
```


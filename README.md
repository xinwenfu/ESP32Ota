# Basic OTA via WiFi on ESP32

This project demonstrates how to use the Over The Air (OTA) update system on an ESP32 board. It also shows the danger of OTA without security. If security is not considered for the OTA, an adversary may inject a malicious firmware into a victim device through the OTA. For secure OTA updates through https, refer to [Get Started With Secure ESP32 OTA through HTTPS](https://github.com/PBearson/Get-Started-With-ESP32-OTA).


## Setup
1. If it is not already configured, It is necessary to configure the Ubuntu VM to use the bridged adaptor. This can be changed using the steps below
   * VirtualBox Manager -> Ubuntu IoT -> Settings -> Network -> Adapter 1 -> Bridged Adapter

2. If not already installed, open a terminal on the Ubuntu VM, and use the following command to install networking tools.
   ```sh 
   sudo apt install net-tools
   ```

   Once we have finished installing *net-tools* we can use them to determine the IP address of the Ubuntu VM with the following command
   ```sh
   sudo ifconfig
   ```

3. Clone this GitHub project to a folder on the Ubuntu VM.
   **Note**: By default, this project is already located in the ``` ~/esp/IoT-Examples/ ``` directory of the Ubuntu VM.

   ```sh
   git clone https://github.com/xinwenfu/ota.git   # Clone the GitHub repository
   ```
   The # symbol indicates the rest of the line is comment.

4. Open VS Code and import this GitHub project, which is an Arduino project.
   - Click file Icon
   - Click *Open Folder* 
   - Click on the *ota* directory that we cloned

### ESP-IDF Setup
1. Enter into the esp-idf directory or install [esp-idf](https://github.com/espressif/esp-idf)
    ```sh
    # Installing ESP-IDF
    cd ~ && \                                           # Enter into the home directory
    mkdir esp && \                                      # Create esp folder
    cd esp && \                                         # Enter into the esp folder
    git clone https://github.com/espressif/esp-idf.git  # Clone esp-idf
    ```
2. Switch the esp-idf repository to release version 5.1 
    ```sh 
    git switch release/v5.1
    ```
3. Run the install script located in the newly cloned ``` esp-idf ``` repository
    ```sh 
    ./install.sh
    ```

### Arduino component setup
The following instructions should be done within the *project repository* ``` ota ```. Additionally if you downloaded this repository correctly **steps 1, 2, and 3 will already have been done for you**. When using the *provided VM* all of this has already been done for you.


**Notice**: When running a project with the arduino core for the first time the ``` idf.py ``` commands will *fail*. We need to edit the generated SDKCONFIG to increase the ``` CONFIG_FREERTOS_HZ ``` value. You may have to do this with a text editor such as nano using ``` nano sdkconfig ```.
``` 
# Before 
CONFIG_FREERTOS_HZ=100

# After 
CONFIG_FREERTOS_HZ=1000
```

1. Now **Install** the [arduino-esp library](https://github.com/espressif/arduino-esp32) into a folder named arduino
    ```sh
    # Clone into arduino-esp32 repository into a directory ./components/arduino
    git clone https://github.com/espressif/arduino-esp32 components/arduino  # Clone arduino core
    ```
2. Enter into the component arduino library
    ```sh
    cd components/arduino 
    ```
3. Switch the branch used by the arduino repository
    ```sh
    git switch esp-idf-v5.1-libs
    ```
4. Modify the ``` components/arduino/CMakeList.txt ``` so the esp_partition can be located.
    ```
    # Before
    set(requires spi_flash mbedtls mdns wifi_provisioning wpa_supplicant esp_adc esp_eth http_parse)

    # After
    set(requires spi_flash mbedtls mdns wifi_provisioning wpa_supplicant esp_adc esp_eth http_parser esp_partition)
    ``` 
5. Move back to the *ota* project directory, otherwise the menuconfig will not work.
    ```sh
    cd ../..
    ```
6. Enabled backwards compatibility within FREERTOS
    ```sh
    # compoent config -> FreeRtos -> Kernel -> configENABLE_BACKWARDS_COMPATIBILITY 
    idf.py menuconfig 
    ```
7.  Enable Enable pre-shaired-cipher suites 
    ```sh
    #  Component config -> mbedTLS -> TLS Key Exchange Methods -> Enable pre shared-key ciphersuites
    #  Component config -> mbedTLS -> TLS Key Exchange Methods -> Enable PSK based ciphersuite modes
    idf.py menuconfig   
    ```
8. Add necessary component dependency
    ```sh
    idf.py add-dependency "espressif/mdns^1.1.0"
    ```

## Flashing the board for the first time via micro USB

1. Using the button located at the bottom of VS Code or a esp-idf terminal and the ``` idf.py menuconfig ``` command edit the SSID and Password 
   ```
   # Example Configuration -> WIFI_SSID
   # Example Configuration -> WIFI_PASSWORD
   idf.py menuconfig
   ```
2. Modify the configuration to support OTA
   1. Configure Factory and two OTA partitions
      ```sh
      # Partition Table -> Partition Table -> Factory app, two OTA definitions
      idf.py menuconfig
      ```
   2. Configure flash memory
      ```sh
      # Serial flasher config -> Flash size -> 4 MB
      idf.py menuconfig
      ```
3. Build the project.
4. Upload the firmware via micro USB.
   - The first installation of the firmware will need to be over the micro USB cable. The code that is built contains OTA functionality and once flashed into the SaTC ESP32 PCB board will be running and waiting for later OTA requests.
   - Press and hold the BOOT button (IO0) of the ESP32 board until the upload starts, in some cases this may not be needed.

5. The newly uploaded firmware blinks the blue LED on the board at a regular interval.
   - The ESP32 board is ready for upgrading through OTA if the blue LED on the board blinks

6. Use the Serial Monitor to see the output from the ESP board firmware, which prints out the IP address of the board

## OTA via WiFi

1. Change the code, e.g, the frequency of the LED light blinking. In the code snippet below, the *delay* function controls the frequency of the blinking.

   ```c
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(1000);                       // wait for a second
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   delay(1000);                       // wait for a second
   ```
2. Build the project.
3. Upload the firmware via OTA using the ``` components/arduino/tools/espota.py ``` tool. The command is shown below (We assume this is ran from the directory containing the espota.py)
   ```
   # Enter the arduino tools directory
   cd components/arduino/tools
   # Be careful of firewall issues blocking the communication
   ./espota.py -d -i [INSERT-ESP-IP] -f path/to/build/file.bin
   ```
   * This will fail if you have a firewall blocking packets, or are not using a Bridged Network adapter!
4.  Notice the different uploading process when compared to the uploading process via micro USB


## Notes

This project is based on https://github.com/atomic14/ESP32Ota. 
Click the image to watch the original demo video with Arduino IDE.

[![Demo Video](https://img.youtube.com/vi/_bMsrxiyuHs/0.jpg)](https://www.youtube.com/watch?v=_bMsrxiyuHs)

In the Arduino IDE, once the sketch is running you can go to "Tools" -> "Ports" and you should find your ESP32 listed as "esp_test". You can change the name of your device by changing this line of code:
```
ArduinoOTA.setHostname("esp_test");
```

This project has been modified to use the esp-arduino core, and esp-idf menuconfig to set the SSID and Password, this can be done using a header file, as show in the video above. 

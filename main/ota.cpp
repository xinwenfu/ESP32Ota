#include <ArduinoOTA.h>
#define LED_BUILTIN 2

IPAddress ip;

// Wifi Defines
// WIFI Defines
// These are from the station example reference linked to at the wifi function comment
/* The examples use WiFi configuration that you can set via project configuration menu
   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_WIFI_SSID CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS CONFIG_ESP_WIFI_PASSWORD
// End WIFI


void setup() {
  Serial.setRxBufferSize(2048);
  Serial.begin(115200);
  Serial.printf("Started up\n");

  WiFi.mode(WIFI_STA);
  WiFi.begin(CONFIG_ESP_WIFI_SSID, CONFIG_ESP_WIFI_PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setHostname("esp_test");
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
      Serial.println("Started updating: " + type);
    })
    .onEnd([]() {
      Serial.println("Update complete");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      unsigned int percent = progress / (total / 100);
      digitalWrite(2, (percent % 2) == 1 ? HIGH : LOW);
      Serial.printf("Progress: %u%%\n", percent);
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR)
        Serial.printf("Auth Faile\n");
      else if (error == OTA_BEGIN_ERROR)
        Serial.printf("Begin Failed\n");
      else if (error == OTA_CONNECT_ERROR)
        Serial.printf("Connect Failed\n");
      else if (error == OTA_RECEIVE_ERROR)
        Serial.printf("Receive Failed\n");
      else if (error == OTA_END_ERROR)
        Serial.printf("End Failed\n");
    });

  ArduinoOTA.begin();
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1500);                       // wait for a second

  Serial.printf("IP address of this esp32 board:");
  ip = WiFi.localIP();
  Serial.println(ip);
  Serial.println("Change Now!");
  
  ArduinoOTA.handle();
}

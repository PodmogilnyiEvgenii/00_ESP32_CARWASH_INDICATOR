void web_task(void * pvParameters) {
  for (;;) {
    if (service_mode) {
      if (WiFi.getMode() == 0) {       

        WiFi.softAP(ESP_name);
        delay(2000);
        WiFi.softAPConfig(ESP_IP, ESP_IP, ESP_SUBNET);

        web_server.onNotFound( [](AsyncWebServerRequest * request) {
          request->send(SPIFFS, "/index.html", String(), false, processor);
        });

        web_server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
          request->send(SPIFFS, "/style.css", "text/css");
        });

        web_server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest * request) {
          request->send(SPIFFS, "/script.js", "text/javascript");
        });

        web_server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
          request->send(SPIFFS, "/index.html", String(), false, processor);
        });       

        dns_server.start(DNS_PORT, "*", ESP_IP);
        AsyncElegantOTA.begin(&web_server);
        web_server.begin();
        Serial.println("Service AP done");
      }
      dns_server.processNextRequest();
    }         
    vTaskDelay(10);
  }
  vTaskDelete(NULL);
}

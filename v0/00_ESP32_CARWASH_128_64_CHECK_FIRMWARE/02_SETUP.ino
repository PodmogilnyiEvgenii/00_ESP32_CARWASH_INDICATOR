void setup() {   

  pinMode(SERVICE_PIN, INPUT_PULLUP);
  pinMode(SERVICE_LED, OUTPUT);
  Serial.begin(115200);
  delay(100);

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS error");     
  } else {
    Serial.println("SPIFFS done");
  }  

  if (digitalRead(SERVICE_PIN)) {                        
    service_mode = false;
    config_modbus();
  } else {                                               
    service_mode = true;    
  }

  digitalWrite(SERVICE_LED, service_mode);
  Serial.print("Service mode "); Serial.println(service_mode);

  HUB75_I2S_CFG::i2s_pins _pins = {R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
  HUB75_I2S_CFG mxconfig(PANEL_WIDTH, PANEL_HEIGHT,  PANELS_NUMBER, _pins, HUB75_I2S_CFG::SHIFTREG);
  matrix = new MatrixPanel_I2S_DMA(mxconfig);
  matrix->setBrightness8(255);
  matrix->begin();
  matrix->clearScreen();   
  matrix_buff = new VirtualMatrixPanel_FastLED_Pixel_Buffer((*matrix), 1, 1, PANEL_WIDTH, PANEL_HEIGHT, true, false);
  matrix_buff->allocateMemory();
  matrix_buff->setTextWrap(false);

  xTaskCreatePinnedToCore(mb_registers_task, "mb_registers_task", 5 * 1024, NULL, 1, &mb_registers_task_, 0);
  xTaskCreatePinnedToCore(web_task, "web_task", 5 * 1024, NULL, 1, &web_task_, 0);

  uint64_t chipid = ESP.getEfuseMac();
  snprintf(ESP_name, 17, "CARWASH_%08X", (uint32_t)chipid);

  Serial.print("Setup done "); Serial.println(ESP_name);  
}

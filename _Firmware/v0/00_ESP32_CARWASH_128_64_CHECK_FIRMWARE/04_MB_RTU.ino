void config_modbus() {
  Serial2.begin(MB_SPEED, SERIAL_8N1, RX_485, TX_485);
  mb.begin(&Serial2);
  mb.slave(MB_ADDRESS);
  mb.addHreg(MB_UPTIME, millis() / 1000);
  Serial.print("Modbus done:"); Serial.print(" speed - " + String(MB_SPEED)); Serial.println(" / address - " + String(MB_ADDRESS));
}

void mb_registers_task(void * pvParameters) {
  for (;;) {
    if (!service_mode) {
      mb.Hreg(MB_UPTIME, millis() / 1000);
      mb.task();
    }
    vTaskDelay(10);
  }
  vTaskDelete(NULL);
}

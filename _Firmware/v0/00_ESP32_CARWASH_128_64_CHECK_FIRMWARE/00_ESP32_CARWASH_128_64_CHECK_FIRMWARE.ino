#include <WiFi.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <AsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <SPIFFS.h>
#include <ModbusRTU.h>
#include <HardwareSerial.h>
#include "FastLED_Pixel_Buffer.h"
#include "LCD7x6.h"

unsigned long to_print_matrix = 25;
unsigned long lt_print_matrix = -to_print_matrix;

int r[13] = {255,  255,  255,  255,  170,    0,     0,    0,    0,    0,  170,  255,  255};
int g[13] = {255,    0,  170,  255,  255,  255,   255,  255,  170,    0,    0,    0,    0};
int b[13] = {255,    0,    0,    0,    0,    0,   170,  255,  255,  255,  255,  255,  128};

// ============================================================================================================================================================================

#define R1_PIN 33
#define G1_PIN 14
#define B1_PIN 26
#define R2_PIN 18
#define G2_PIN 4
#define B2_PIN 19

#define A_PIN 23
#define B_PIN 32
#define C_PIN 5
#define D_PIN 25
#define E_PIN 12

#define LAT_PIN 27
#define OE_PIN 22
#define CLK_PIN 21

#define PANEL_WIDTH 128
#define PANEL_HEIGHT 64
#define PANELS_NUMBER 1

MatrixPanel_I2S_DMA *matrix = nullptr;
VirtualMatrixPanel_FastLED_Pixel_Buffer  *matrix_buff = nullptr;

// ============================================================================================================================================================================

#define MB_ADDRESS           100
#define MB_SPEED             57600  
#define RX_485               16
#define TX_485               17
#define MB_UPTIME            100 
ModbusRTU mb;

// ============================================================================================================================================================================

#define DNS_PORT              53
IPAddress ESP_IP(192, 168, 1, 1);
IPAddress ESP_SUBNET(255, 255, 255, 0);
AsyncWebServer web_server(80);
DNSServer dns_server;
char ESP_name[17];

// ============================================================================================================================================================================

String processor(const String& var) {
  String data_var = "";  
  if (var == "ESP_NAME") {
    data_var = String(ESP_name);
    return data_var;
  }
  return String();
}

// ============================================================================================================================================================================

#define SERVICE_PIN          13
#define SERVICE_LED          2
bool service_mode = false;

// ============================================================================================================================================================================

TaskHandle_t mb_registers_task_;
TaskHandle_t web_task_;

void blank_prog() {
}

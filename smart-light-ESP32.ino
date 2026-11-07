

#include <WiFi.h>
#include <WebServer.h>
#include "web_ui.h"  // Tampilan antarmuka Web UI dipisah di berkas header tersendiri

// Definisi 3 Pin LED
const int LED1_PIN = 2; // Lampu 1 (Ruang Tamu)
const int LED2_PIN = 4; // Lampu 2 (Kamar Tidur)
const int LED3_PIN = 5; // Lampu 3 (Dapur)

// Konfigurasi Wi-Fi Hotspot Mandiri
const char *ssid = "ESP32_Smart_Light";
const char *password = "12345678";

WebServer server(80);

// Status lampu (Mode Manual)
bool led1State = false;
bool led2State = false;
bool led3State = false;

// ----------------------------------------------------------------------------
// Engine Animasi Lampu Dinamis (Non-Blocking millis)
// 0: Normal / Manual
// 1: Strobo Blitz (Kedip Cepat Frekuensi Tinggi)
// 2: Running Wave (Lampu Berjalan 1 -> 2 -> 3 Bergantian)
// 3: Dual Hazard (Kedip Silang Ganda ala Hazard Patroli)
// ----------------------------------------------------------------------------
int currentMode = 0;
unsigned long lastEffectTime = 0;
int effectStep = 0;

// Helper: Mengirim respon status format JSON ke browser smartphone
void sendStateResponse() {
  String json = "{";
  json += "\"l1\":" + String(led1State ? "true" : "false") + ",";
  json += "\"l2\":" + String(led2State ? "true" : "false") + ",";
  json += "\"l3\":" + String(led3State ? "true" : "false") + ",";
  json += "\"mode\":" + String(currentMode);
  json += "}";
  server.send(200, "application/json", json);
}

// Handler Halaman Utama (Mengirim HTML dari web_ui.h dengan No-Cache Header)
void handleRoot() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(200, "text/html", HTML_PAGE);
}

// Handlers Kontrol Manual Lampu 1 (GPIO 2)
void handleL1On() {
  currentMode = 0;
  led1State = true;
  digitalWrite(LED1_PIN, HIGH);
  sendStateResponse();
}
void handleL1Off() {
  currentMode = 0;
  led1State = false;
  digitalWrite(LED1_PIN, LOW);
  sendStateResponse();
}

// Handlers Kontrol Manual Lampu 2 (GPIO 4)
void handleL2On() {
  currentMode = 0;
  led2State = true;
  digitalWrite(LED2_PIN, HIGH);
  sendStateResponse();
}
void handleL2Off() {
  currentMode = 0;
  led2State = false;
  digitalWrite(LED2_PIN, LOW);
  sendStateResponse();
}

// Handlers Kontrol Manual Lampu 3 (GPIO 5)
void handleL3On() {
  currentMode = 0;
  led3State = true;
  digitalWrite(LED3_PIN, HIGH);
  sendStateResponse();
}
void handleL3Off() {
  currentMode = 0;
  led3State = false;
  digitalWrite(LED3_PIN, LOW);
  sendStateResponse();
}

// Handlers Master (Semua ON / Semua OFF)
void handleAllOn() {
  currentMode = 0;
  led1State = led2State = led3State = true;
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  digitalWrite(LED3_PIN, HIGH);
  sendStateResponse();
}

void handleAllOff() {
  currentMode = 0;
  led1State = led2State = led3State = false;
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  sendStateResponse();
}

// Handlers Mode Animasi (Mode 0, 1, 2, 3)
void handleSetMode() {
  if (server.hasArg("val")) {
    int requestedMode = server.arg("val").toInt();
    if (requestedMode >= 0 && requestedMode <= 3) {
      currentMode = requestedMode;
      effectStep = 0;
      lastEffectTime = millis();

      // Jika kembali ke mode 0 (Normal Matikan Semua)
      if (currentMode == 0) {
        led1State = led2State = led3State = false;
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, LOW);
      }
    }
  }
  sendStateResponse();
}

// ----------------------------------------------------------------------------
// Rutinitas Animasi Efek Dinamis (Dijalankan di loop secara non-blocking)
// ----------------------------------------------------------------------------
void updateLightingEffects() {
  if (currentMode == 0) return; // Mode manual tidak memerlukan animasi

  unsigned long currentMillis = millis();

  // Mode 1: Strobo Blitz (Kedip Cepat Serentak 90ms ON / 90ms OFF)
  if (currentMode == 1) {
    if (currentMillis - lastEffectTime >= 90) {
      lastEffectTime = currentMillis;
      effectStep = !effectStep;
      digitalWrite(LED1_PIN, effectStep ? HIGH : LOW);
      digitalWrite(LED2_PIN, effectStep ? HIGH : LOW);
      digitalWrite(LED3_PIN, effectStep ? HIGH : LOW);
    }
  }

  // Mode 2: Running Wave (Lampu Berjalan 1 -> 2 -> 3 Bergantian, 140ms per step)
  else if (currentMode == 2) {
    if (currentMillis - lastEffectTime >= 140) {
      lastEffectTime = currentMillis;
      effectStep = (effectStep + 1) % 3;
      digitalWrite(LED1_PIN, effectStep == 0 ? HIGH : LOW);
      digitalWrite(LED2_PIN, effectStep == 1 ? HIGH : LOW);
      digitalWrite(LED3_PIN, effectStep == 2 ? HIGH : LOW);
    }
  }

  // Mode 3: Dual Hazard Police (Kedip Silang Ganda: 1 & 2 Blitz, lalu 3 Blitz)
  else if (currentMode == 3) {
    if (currentMillis - lastEffectTime >= 85) {
      lastEffectTime = currentMillis;
      effectStep = (effectStep + 1) % 8;
      // Step 0 & 2: Lampu 1 & 2 ON
      // Step 4 & 6: Lampu 3 ON
      // Step lainnya: OFF (Jeda blitz)
      if (effectStep == 0 || effectStep == 2) {
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, HIGH);
        digitalWrite(LED3_PIN, LOW);
      } else if (effectStep == 4 || effectStep == 6) {
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, HIGH);
      } else {
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, LOW);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Inisialisasi 3 Pin GPIO sebagai OUTPUT
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  // Kondisi awal lampu padam
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);

  // Aktifkan Wi-Fi Access Point (Hotspot)
  Serial.println("\n[SYSTEM] Memulai Wi-Fi Access Point...");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("[SYSTEM] Hotspot Aktif! Alamat IP: http://");
  Serial.println(IP);

  // Routing Endpoint REST API
  server.on("/", HTTP_GET, handleRoot);
  server.on("/status", HTTP_GET, sendStateResponse);

  // Endpoint Kontrol Lampu Satuan
  server.on("/on1", HTTP_GET, handleL1On);
  server.on("/off1", HTTP_GET, handleL1Off);

  server.on("/on2", HTTP_GET, handleL2On);
  server.on("/off2", HTTP_GET, handleL2Off);

  server.on("/on3", HTTP_GET, handleL3On);
  server.on("/off3", HTTP_GET, handleL3Off);

  // Endpoint Master
  server.on("/all/on", HTTP_GET, handleAllOn);
  server.on("/all/off", HTTP_GET, handleAllOff);

  // Endpoint Efek Animasi (/mode?val=1|2|3|0)
  server.on("/mode", HTTP_GET, handleSetMode);

  // Menjalankan Web Server
  server.begin();
  Serial.println("[SYSTEM] HTTP REST Server Siap melayani permintaan.");
}

void loop() {
  // Melayani permintaan HTTP dari smartphone secara non-blocking
  server.handleClient();

  // Menjalankan animasi efek lampu dinamis jika ada mode aktif
  updateLightingEffects();
}

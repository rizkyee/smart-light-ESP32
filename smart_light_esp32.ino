/*
 * Project: Smart Light ESP32 - Kontrol 3 Lampu LED
 * UI Style: Framework7 / Apple HomeKit (3 Independent Toggles)
 * Pinout:
 *   - Lampu 1 (Ruang Tamu) : GPIO 2 (P2)
 *   - Lampu 2 (Kamar Tidur): GPIO 4 (P4)
 *   - Lampu 3 (Dapur)      : GPIO 5 (P5)
 * Mode: Access Point (192.168.4.1) - 100% Offline
 */

#include <WiFi.h>
#include <WebServer.h>

// Definisi 3 Pin LED
const int LED1_PIN = 2; // Lampu 1
const int LED2_PIN = 4; // Lampu 2
const int LED3_PIN = 5; // Lampu 3

// Konfigurasi Hotspot ESP32
const char *ssid = "ESP32_Smart_Light";
const char *password = "12345678";

WebServer server(80);

// Status awal 3 lampu
bool led1State = false;
bool led2State = false;
bool led3State = false;

// Halaman Web Framework7 / iOS Style dengan 3 Tombol Lampu
const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Smart Home - 3 Lampu ESP32</title>
  <style>
    :root {
      --ios-green: #34c759;
      --ios-bg: #f2f2f7;
      --ios-card-bg: #ffffff;
      --ios-text: #000000;
      --ios-subtext: #8e8e93;
      --ios-border: #e5e5ea;
    }

    @media (prefers-color-scheme: dark) {
      :root {
        --ios-bg: #000000;
        --ios-card-bg: #1c1c1e;
        --ios-text: #ffffff;
        --ios-subtext: #8e8e93;
        --ios-border: #2c2c2e;
      }
    }

    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      -webkit-tap-highlight-color: transparent;
      font-family: -apple-system, BlinkMacSystemFont, "SF Pro Display", Roboto, Helvetica, Arial, sans-serif;
    }

    body {
      background-color: var(--ios-bg);
      color: var(--ios-text);
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 20px 16px;
    }

    .header-bar {
      width: 100%;
      max-width: 420px;
      padding: 12px 6px 20px;
    }
    .header-bar h1 {
      font-size: 30px;
      font-weight: 700;
      letter-spacing: -0.5px;
    }
    .header-bar p {
      font-size: 13px;
      color: var(--ios-subtext);
      margin-top: 2px;
    }

    /* List Inset Grouped Card */
    .inset-list {
      background-color: var(--ios-card-bg);
      width: 100%;
      max-width: 420px;
      border-radius: 18px;
      border: 1px solid var(--ios-border);
      box-shadow: 0 4px 20px rgba(0, 0, 0, 0.05);
      overflow: hidden;
      margin-bottom: 20px;
    }

    .device-item {
      display: flex;
      align-items: center;
      justify-content: space-between;
      padding: 16px 18px;
      border-bottom: 1px solid var(--ios-border);
    }
    .device-item:last-child {
      border-bottom: none;
    }

    .device-left {
      display: flex;
      align-items: center;
      gap: 14px;
    }

    .device-icon {
      width: 46px;
      height: 46px;
      border-radius: 12px;
      background-color: rgba(142, 142, 147, 0.15);
      display: flex;
      align-items: center;
      justify-content: center;
      font-size: 22px;
      transition: background-color 0.25s ease, transform 0.2s ease;
    }
    .device-icon.active {
      background-color: rgba(250, 204, 21, 0.25);
      transform: scale(1.05);
    }

    .device-title {
      font-size: 16px;
      font-weight: 600;
      letter-spacing: -0.3px;
    }
    .device-desc {
      font-size: 12px;
      color: var(--ios-subtext);
      margin-top: 2px;
    }

    /* Framework7 / iOS Toggle Switch */
    .f7-toggle {
      position: relative;
      display: inline-block;
      width: 52px;
      height: 32px;
      cursor: pointer;
    }
    .f7-toggle input {
      opacity: 0;
      width: 0;
      height: 0;
    }
    .f7-slider {
      position: absolute;
      top: 0; left: 0; right: 0; bottom: 0;
      background-color: #e9e9ea;
      border-radius: 34px;
      transition: background-color 0.3s cubic-bezier(0.25, 0.1, 0.25, 1);
    }
    .f7-slider::before {
      position: absolute;
      content: "";
      height: 28px;
      width: 28px;
      left: 2px;
      bottom: 2px;
      background-color: #ffffff;
      border-radius: 50%;
      box-shadow: 0 3px 8px rgba(0, 0, 0, 0.15), 0 3px 1px rgba(0, 0, 0, 0.06);
      transition: transform 0.3s cubic-bezier(0.25, 0.1, 0.25, 1);
    }
    .f7-toggle input:checked + .f7-slider {
      background-color: var(--ios-green);
    }
    .f7-toggle input:checked + .f7-slider::before {
      transform: translateX(20px);
    }

    /* Master Action Buttons */
    .master-actions {
      display: flex;
      gap: 10px;
      width: 100%;
      max-width: 420px;
    }
    .btn-action {
      flex: 1;
      padding: 12px;
      border-radius: 12px;
      border: 1px solid var(--ios-border);
      background: var(--ios-card-bg);
      color: var(--ios-text);
      font-weight: 600;
      font-size: 13px;
      cursor: pointer;
      transition: opacity 0.2s;
    }
    .btn-action:active {
      opacity: 0.6;
    }

    .footer {
      margin-top: auto;
      padding-top: 24px;
      font-size: 12px;
      color: var(--ios-subtext);
      text-align: center;
    }
  </style>
</head>
<body>

  <div class="header-bar">
    <h1>Smart Lights</h1>
    <p>3-Channel ESP32 Control Center</p>
  </div>

  <div class="inset-list">
    <!-- LAMPU 1 -->
    <div class="device-item">
      <div class="device-left">
        <div class="device-icon" id="icon1">💡</div>
        <div>
          <div class="device-title">Lampu 1 (Ruang Tamu)</div>
          <div class="device-desc" id="desc1">GPIO 2 • Mati</div>
        </div>
      </div>
      <label class="f7-toggle">
        <input type="checkbox" id="toggle1" onchange="switchLamp(1, this.checked)">
        <span class="f7-slider"></span>
      </label>
    </div>

    <!-- LAMPU 2 -->
    <div class="device-item">
      <div class="device-left">
        <div class="device-icon" id="icon2">💡</div>
        <div>
          <div class="device-title">Lampu 2 (Kamar Tidur)</div>
          <div class="device-desc" id="desc2">GPIO 4 • Mati</div>
        </div>
      </div>
      <label class="f7-toggle">
        <input type="checkbox" id="toggle2" onchange="switchLamp(2, this.checked)">
        <span class="f7-slider"></span>
      </label>
    </div>

    <!-- LAMPU 3 -->
    <div class="device-item">
      <div class="device-left">
        <div class="device-icon" id="icon3">💡</div>
        <div>
          <div class="device-title">Lampu 3 (Dapur)</div>
          <div class="device-desc" id="desc3">GPIO 5 • Mati</div>
        </div>
      </div>
      <label class="f7-toggle">
        <input type="checkbox" id="toggle3" onchange="switchLamp(3, this.checked)">
        <span class="f7-slider"></span>
      </label>
    </div>
  </div>

  <!-- Tombol Aksi Cepat -->
  <div class="master-actions">
    <button class="btn-action" onclick="setAllLamps(true)">Nyalakan Semua</button>
    <button class="btn-action" onclick="setAllLamps(false)">Matikan Semua</button>
  </div>

  <div class="footer">
    Terhubung ke ESP32 Access Point (192.168.4.1)
  </div>

  <script>
    function updateLampUI(num, state) {
      const toggle = document.getElementById('toggle' + num);
      const icon = document.getElementById('icon' + num);
      const desc = document.getElementById('desc' + num);
      const gpios = {1: 'GPIO 2', 2: 'GPIO 4', 3: 'GPIO 5'};

      toggle.checked = state;
      if (state) {
        icon.classList.add('active');
        desc.innerText = gpios[num] + ' • Menyala';
        desc.style.color = '#34c759';
      } else {
        icon.classList.remove('active');
        desc.innerText = gpios[num] + ' • Mati';
        desc.style.color = 'var(--ios-subtext)';
      }
    }

    function switchLamp(lampNum, isChecked) {
      const endpoint = isChecked ? `/on${lampNum}` : `/off${lampNum}`;
      fetch(endpoint)
        .then(res => res.json())
        .then(data => {
          updateLampUI(1, data.l1);
          updateLampUI(2, data.l2);
          updateLampUI(3, data.l3);
        })
        .catch(err => {
          console.error(err);
          document.getElementById('toggle' + lampNum).checked = !isChecked;
          alert('Gagal mengirim perintah ke ESP32!');
        });
    }

    function setAllLamps(turnOn) {
      const endpoint = turnOn ? '/all/on' : '/all/off';
      fetch(endpoint)
        .then(res => res.json())
        .then(data => {
          updateLampUI(1, data.l1);
          updateLampUI(2, data.l2);
          updateLampUI(3, data.l3);
        });
    }

    // Ambil status 3 lampu saat halaman pertama dibuka
    fetch('/status')
      .then(res => res.json())
      .then(data => {
        updateLampUI(1, data.l1);
        updateLampUI(2, data.l2);
        updateLampUI(3, data.l3);
      });
  </script>
</body>
</html>
)rawliteral";

// Helper untuk mengirim status format JSON
void sendStateResponse() {
  String json = "{";
  json += "\"l1\":" + String(led1State ? "true" : "false") + ",";
  json += "\"l2\":" + String(led2State ? "true" : "false") + ",";
  json += "\"l3\":" + String(led3State ? "true" : "false");
  json += "}";
  server.send(200, "application/json", json);
}

void handleRoot() {
  server.send(200, "text/html", HTML_PAGE);
}

// Handler Lampu 1
void handleL1On()  { led1State = true;  digitalWrite(LED1_PIN, HIGH); sendStateResponse(); }
void handleL1Off() { led1State = false; digitalWrite(LED1_PIN, LOW);  sendStateResponse(); }

// Handler Lampu 2
void handleL2On()  { led2State = true;  digitalWrite(LED2_PIN, HIGH); sendStateResponse(); }
void handleL2Off() { led2State = false; digitalWrite(LED2_PIN, LOW);  sendStateResponse(); }

// Handler Lampu 3
void handleL3On()  { led3State = true;  digitalWrite(LED3_PIN, HIGH); sendStateResponse(); }
void handleL3Off() { led3State = false; digitalWrite(LED3_PIN, LOW);  sendStateResponse(); }

// Handler Master
void handleAllOn() {
  led1State = led2State = led3State = true;
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  digitalWrite(LED3_PIN, HIGH);
  sendStateResponse();
}

void handleAllOff() {
  led1State = led2State = led3State = false;
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  sendStateResponse();
}

void setup() {
  Serial.begin(115200);

  // Inisialisasi 3 Pin sebagai OUTPUT
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);

  // Mode Access Point (Hotspot)
  WiFi.softAP(ssid, password);

  // Daftarkan Endpoint API
  server.on("/", HTTP_GET, handleRoot);
  server.on("/status", HTTP_GET, sendStateResponse);

  server.on("/on1", HTTP_GET, handleL1On);
  server.on("/off1", HTTP_GET, handleL1Off);

  server.on("/on2", HTTP_GET, handleL2On);
  server.on("/off2", HTTP_GET, handleL2Off);

  server.on("/on3", HTTP_GET, handleL3On);
  server.on("/off3", HTTP_GET, handleL3Off);

  server.on("/all/on", HTTP_GET, handleAllOn);
  server.on("/all/off", HTTP_GET, handleAllOff);

  server.begin();
  Serial.println("Web Server 3 Lampu Siap di http://192.168.4.1");
}

void loop() {
  server.handleClient();
}

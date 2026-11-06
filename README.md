# 💡 Smart Light ESP32 - Multi-Channel (3 LEDs) Controller

Sistem kendali lampu nirkabel multi-saluran berbasis **ESP32** yang dioperasikan secara lokal (*offline*) melalui antarmuka web modern bergaya **Apple HomeKit / Framework7** pada smartphone.

---

## 🛠️ Teknologi & Bahasa yang Digunakan

<div align="left">
  <img src="https://img.shields.io/badge/Hardware-ESP32%20NodeMCU-E7352C?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32" />
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino IDE" />
  <img src="https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white" alt="HTML5" />
  <img src="https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white" alt="CSS3" />
  <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black" alt="JavaScript" />
  <img src="https://img.shields.io/badge/UI_Concept-Framework7%20%2F%20iOS-007AFF?style=for-the-badge&logo=apple&logoColor=white" alt="Framework7" />
</div>

---

## ✨ Fitur Utama

- **100% Bebas Kuota (Offline):** Berjalan di mode **Access Point (AP)** mandiri. ESP32 memancarkan sinyal Wi-Fi sendiri tanpa memerlukan router atau kuota internet.
- **Tanpa Instalasi Aplikasi (Zero-Install):** Cukup buka browser bawaan HP (Safari, Chrome) dan masukkan IP default `http://192.168.4.1`.
- **Kendali Multi-Channel:** Mengontrol 3 lampu secara independen maupun serentak (*Nyalakan Semua / Matikan Semua*).
- **Respon Cepat Tanpa Reload (Fetch API):** Menggunakan AJAX/Fetch API asinkron sehingga status lampu berganti seketika dengan animasi toggle switch iOS yang mulus.
- **Proteksi Rangkaian:** Masing-masing LED diproteksi dengan resistor mandiri (100Ω / 1kΩ) untuk menjaga kestabilan arus.

---

## 📦 Komponen & Bahan

| Komponen | Spesifikasi / Tipe | Jumlah |
|---|---|---|
| **Mikrokontroler** | NodeMCU ESP-32S (38-Pin v1.1) | 1 unit |
| **Lampu LED** | LED Diffused 5mm (Merah / Hijau / dsb.) | 3 buah |
| **Resistor** | Metal Film 5-Gelang (100Ω / 1kΩ) | 3 buah |
| **Breadboard** | Solderless White Breadboard (400 Lubang, 30 Baris) | 1 unit |
| **Kabel Jumper** | Male-to-Male (Colokan Jarum) | 4 pcs |

---

## 🔌 Skema Pin & Titik Lubang Breadboard

Untuk memudahkan pemula, seluruh komponen dirakit menyatu di satu papan breadboard 400 lubang:
- **ESP32:** Ditancapkan di bagian atas (**Baris 1 sampai 19**).
- **Kolom J (Sisi Kanan ESP32):** Menjadi titik colokan kabel output sinyal.

| Saluran | Pin ESP32 | Titik Colokan Breadboard | Tujuan / Kaki Komponen |
|---|---|---|---|
| **Lampu 1 (Ruang Tamu)** | `P2` (GPIO 2) | **Lubang J14** ➔ **F22** | Kaki Panjang (Anoda +) LED 1 |
| **Lampu 2 (Kamar Tidur)** | `P4` (GPIO 4) | **Lubang J12** ➔ **F25** | Kaki Panjang (Anoda +) LED 2 |
| **Lampu 3 (Dapur)** | `P5` (GPIO 5) | **Lubang J9** ➔ **F28** | Kaki Panjang (Anoda +) LED 3 |
| **Resistor 1, 2, 3** | - | **G23, G26, G29** ➔ **Rel Biru (-)** | Menahan arus menuju Ground |
| **Ground Bersama** | `GND` | **Lubang J1** ➔ **Rel Biru (-)** | Penutup arus semua saluran |

> 💡 **Panduan Visual Interaktif:** Buka file [`wiring.html`](file:///Users/macbookpro/project-dev/kuliah/smart-light-ESP32/wiring.html) di browser Anda untuk melihat diagram animasi perakitan.

---

## 🚀 Panduan Instalasi & Upload (Arduino IDE)

### 1. Pasang Board ESP32
1. Buka **Arduino IDE** (Versi 2.x).
2. Masuk ke **Settings / Preferences** (`Cmd + ,` di Mac).
3. Tambahkan URL package ESP32 pada kolom *Additional Boards Manager URLs*:
   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Buka menu **Boards Manager**, cari `esp32` by Espressif Systems, lalu klik **Install**.

### 2. Upload Kodingan
1. Buka berkas [`smart_light_esp32.ino`](file:///Users/macbookpro/project-dev/kuliah/smart-light-ESP32/smart_light_esp32.ino).
2. Sambungkan ESP32 ke port USB laptop menggunakan kabel data.
3. Pilih Board: **DOIT ESP32 DEVKIT V1** (atau *ESP32 Dev Module*).
4. Pilih Port USB yang terdeteksi (contoh: `/dev/cu.usbserial-...`).
5. Klik tombol **Upload** (➔).
   *(Jika muncul tulisan `Connecting......._____.....`, tekan dan tahan tombol **BOOT** pada ESP32 selama 1–2 detik).*

---

## 📱 Cara Penggunaan

1. Nyalakan ESP32 (cukup colokkan ke charger HP atau port USB laptop).
2. Dari smartphone Anda, buka menu pengaturan **Wi-Fi**.
3. Hubungkan ke jaringan Wi-Fi:
   - **SSID:** `ESP32_Smart_Light`
   - **Password:** `12345678`
4. Buka browser (Safari / Google Chrome), lalu akses alamat:
   ```text
   http://192.168.4.1
   ```
5. Geser toggle switch pada layar untuk mengontrol nyala dan matinya lampu LED.

---

## 📁 Struktur Berkas Proyek

```text
smart-light-ESP32/
├── .gitignore             # Berkas pengabaian file sampah compiler & OS
├── README.md              # Dokumentasi lengkap proyek
├── PRD.md                 # Product Requirement Document & Naskah Video 5 Menit
├── smart_light_esp32.ino  # Kode sumber C++ ESP32 & Web Server Framework7
├── wiring.html            # Diagram skematik breadboard interaktif
└── assets/                # Dokumentasi foto komponen fisik nyata
```

---

## ⏱️ Rundown Video Tugas (Maksimal 5 Menit)

| Durasi | Segmen | Materi Presentasi |
|---|---|---|
| **00:00 - 00:45** | Pembukaan & Komponen | Perkenalan diri/kelompok, penjelasan tujuan tugas, serta memperlihatkan fisik ESP32, 3 LED, 3 resistor, dan breadboard. |
| **00:45 - 01:30** | Rangkaian Wiring | Tunjukkan fisik breadboard: Sambungan pin P2, P4, P5 ke anoda LED dan rel ground bersama. |
| **01:30 - 03:15** | Penjelasan Coding & Web | Screen record Arduino IDE: Jelaskan konfigurasi `WiFi.softAP`, routing REST API, dan antarmuka web bergaya Framework7/iOS (Pure CSS). |
| **03:15 - 04:30** | Demo Pengujian HP | Tunjukkan koneksi Wi-Fi HP ➔ Masuk `192.168.4.1` ➔ Nyalakan lampu satu per satu dan uji tombol *Semua ON/OFF*. |
| **04:30 - 05:00** | Kesimpulan & Penutup | Ringkasan keberhasilan sistem kendali IoT lokal multi-saluran tanpa internet. Salam penutup. |


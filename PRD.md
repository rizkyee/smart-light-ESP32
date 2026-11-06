# Product Requirement Document (PRD)
## Smart Light ESP32 Controller - Multi-Channel (3 LEDs) via Web Interface

---

## 1. Latar Belakang & Ketentuan Soal (Original Task + Penambahan 3 LED)

> **Deskripsi Tugas Asli:**  
> Membuat aplikasi menggunakan ESP32 yang digunakan untuk menyalakan dan mematikan lampu LED dengan mengontrolnya menggunakan HP yang terkoneksi dengan ESP32.
>
> **Bahan / Komponen yang Digunakan (Update: 3 Saluran):**
> - 1x Board ESP32 (NodeMCU ESP-32S 38-Pin)
> - 3x Lampu LED (Merah, Hijau, dsb. 5mm)
> - 3x Resistor (100Ω / 1kΩ Metal Film - 1 resistor per 1 LED)
> - 1x Breadboard & Kabel Jumper
>
> **Ketentuan Video:**
> - Durasi maksimal: **5 menit**
> - Konten wajib: Menjelaskan coding secara garis besar, terutama arsitektur tampilan antarmuka WEB (Framework7 / iOS Style) untuk 3 lampu.

---

## 2. Tujuan & Sasaran Produk (Objectives & Goals)

1. **Kendali Independen 3 Saluran:** Pengguna dapat mengontrol 3 lampu LED secara terpisah (Lampu 1, Lampu 2, Lampu 3) maupun serentak (Nyalakan Semua / Matikan Semua).
2. **Koneksi Nirkabel Lokal Bebas Kuota:** Berjalan di mode Access Point (AP) mandiri (`192.168.4.1`) tanpa ketergantungan kuota internet.
3. **Antarmuka Mobile-First (Framework7 / iOS HomeKit):** Tampilan Web menyerupai dashboard Apple HomeKit dengan 3 switch toggle animasi khas iOS.
4. **Proteksi Arus Mandiri:** Setiap LED dilindungi oleh 1 resistor mandiri agar nyala lampu stabil dan tidak meredup saat ketiga lampu dinyalakan bersamaan.

---

## 3. Spesifikasi Perangkat Keras (Hardware Architecture)

- **Mikrokontroler:** NodeMCU ESP-32S (38-pin version).
- **Pemilihan Pin GPIO (Sisi Kanan Board):**
  - **Lampu 1 (Ruang Tamu):** **GPIO 2 (P2)**
  - **Lampu 2 (Kamar Tidur):** **GPIO 4 (P4)**
  - **Lampu 3 (Dapur):** **GPIO 5 (P5)**
- **Jalur Ground (GND):** Pin **GND** ESP32 dihubungkan ke **Rel Negatif (-) Breadboard**, tempat bertemunya ketiga kaki resistor.

### Tabel Pemetaan Pin (Pin Mapping 3 LED)
| Komponen | Terminal Komponen | Pin ESP32 / Jalur Breadboard | Keterangan |
|---|---|---|---|
| **LED 1** | Kaki Panjang (Anoda +) | **Pin P2 (GPIO 2)** | Sinyal Kontrol Lampu 1 |
| **LED 1** | Kaki Pendek (Katoda -) | Resistor 1 ➔ **Rel GND (-)** | Pembatas Arus Saluran 1 |
| **LED 2** | Kaki Panjang (Anoda +) | **Pin P4 (GPIO 4)** | Sinyal Kontrol Lampu 2 |
| **LED 2** | Kaki Pendek (Katoda -) | Resistor 2 ➔ **Rel GND (-)** | Pembatas Arus Saluran 2 |
| **LED 3** | Kaki Panjang (Anoda +) | **Pin P5 (GPIO 5)** | Sinyal Kontrol Lampu 3 |
| **LED 3** | Kaki Pendek (Katoda -) | Resistor 3 ➔ **Rel GND (-)** | Pembatas Arus Saluran 3 |
| **ESP32** | Pin GND (Paling Atas) | **Rel Negatif (-) Breadboard** | Jalur Balik Ground Bersama |

---

## 4. Spesifikasi Perangkat Lunak & Web (Software Architecture)

### 4.1 Jaringan & API Endpoints
- **SSID Hotspot:** `ESP32_Smart_Light`
- **Password:** `12345678`
- **IP Server:** `http://192.168.4.1`
- **Daftar Endpoint HTTP:**
  - `GET /` : Memuat dashboard HTML Framework7 / iOS.
  - `GET /status` : Mendapatkan status ketiga lampu dalam JSON: `{"l1":bool,"l2":bool,"l3":bool}`.
  - `GET /on1` & `GET /off1` : Kendali Lampu 1 (GPIO 2).
  - `GET /on2` & `GET /off2` : Kendali Lampu 2 (GPIO 4).
  - `GET /on3` & `GET /off3` : Kendali Lampu 3 (GPIO 5).
  - `GET /all/on` & `GET /all/off` : Master switch kendali serentak 3 lampu.

### 4.2 Desain Web UI
- Menggunakan list grouped card khas iOS dengan 3 tombol switch toggle hijau.
- Dilengkapi tombol cepat *Master Action* (*Nyalakan Semua* dan *Matikan Semua*).
- 100% Pure CSS (Zero Dependency), berjalan instan di smartphone tanpa internet.

---

## 5. Rencana Pembagian Waktu Video (Max 5 Menit)

| Alokasi Waktu | Topik Video | Hal yang Harus Dipaparkan |
|---|---|---|
| **00:00 - 00:45** (45d) | Pembukaan & Pengenalan Alat | Perkenalan diri, tujuan membuat Smart Light 3 Saluran, perkenalan fisik: ESP32 38-pin, 3 LED, 3 Resistor, dan Breadboard. |
| **00:45 - 01:30** (45d) | Skema Rangkaian 3 Saluran | Tunjukkan di breadboard: Pin P2, P4, P5 masing-masing ke Anoda LED 1, 2, 3. Tunjukkan ketiga resistor terhubung ke rel GND bersama. |
| **01:30 - 03:15** (105d) | Bedah Koding & Konsep Web | Rekam Arduino IDE. Jelaskan inisialisasi 3 pin output (`pinMode`), routing endpoint (`/on1`, `/on2`, `/on3`), dan antarmuka web iOS 3 toggle. |
| **03:15 - 04:30** (75d) | Demo Pengujian via HP | Hubungkan HP ke Wi-Fi ESP32 ➔ Buka browser `192.168.4.1` ➔ Nyalakan lampu satu per satu (Lampu 1 ➔ Lampu 2 ➔ Lampu 3) ➔ Uji tombol *Nyalakan Semua* dan *Matikan Semua*. |
| **04:30 - 05:00** (30d) | Kesimpulan & Penutup | Ringkasan keberhasilan sistem kendali multi-channel lokal. Ucapan terima kasih dan penutup. |

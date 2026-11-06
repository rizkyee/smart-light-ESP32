# 💡 Smart Light ESP32 - Multi-Channel (3 LEDs) Controller

Sistem kendali lampu nirkabel multi-saluran berbasis **ESP32 NodeMCU** yang dioperasikan secara mandiri (*100% Offline / Local Access Point*) melalui antarmuka web modern bergaya **Startup Dashboard** pada peramban smartphone maupun desktop.

---

## 🛠️ Teknologi & Arsitektur

<div align="left">
  <img src="https://img.shields.io/badge/Hardware-ESP32%20NodeMCU%20(38--Pin)-E7352C?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32" />
  <img src="https://img.shields.io/badge/Firmware-C%2B%2B%20%2F%20Arduino-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/Frontend-HTML5%20%26%20CSS3-E34F26?style=for-the-badge&logo=html5&logoColor=white" alt="HTML5 & CSS3" />
  <img src="https://img.shields.io/badge/Scripting-JavaScript%20(ES6)-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black" alt="JavaScript" />
  <img src="https://img.shields.io/badge/Protocol-HTTP%20REST%20API-007ACC?style=for-the-badge&logo=fastapi&logoColor=white" alt="REST API" />
  <img src="https://img.shields.io/badge/Design-Clean%20Startup%20White-10B981?style=for-the-badge" alt="Design System" />
</div>

---

## ✨ Fitur Utama

- **100% Bebas Kuota & Router (Offline SoftAP):** ESP32 memancarkan jaringan hotspot Wi-Fi mandiri (`ESP32_Smart_Light`) tanpa memerlukan koneksi internet maupun router eksternal.
- **Tanpa Instalasi Aplikasi (Zero-Install):** Cukup buka peramban bawaan smartphone (Safari, Chrome) dan akses alamat `http://192.168.4.1`.
- **Desain Antarmuka Modern & Bersih:**
  - Bertema putih minimalis (*Startup aesthetic*) dengan tipografi **Plus Jakarta Sans** & **Inter**.
  - Menggunakan **ikon vektor murni SVG** (tanpa emoji) untuk tampilan visual yang konsisten dan profesional.
  - Tata letak **100% Fluid Responsive** yang otomatis menyesuaikan layar ponsel secara presisi tanpa bingkai tiruan.
- **Kendali Multi-Saluran Mandiri & Serentak:**
  - Kontrol manual independen untuk Lampu 1 (Ruang Tamu), Lampu 2 (Kamar Tidur), dan Lampu 3 (Dapur).
  - Tombol aksi serentak (*Master Action*): **Nyalakan Semua** dan **Matikan Semua**.
- **3 Mode Animasi Dinamis (*Non-Blocking Timing*):**
  - **Mode 1 (Strobo Blitz):** Ketiga lampu berkedip frekuensi tinggi secara serentak (90ms ON / 90ms OFF).
  - **Mode 2 (Running Wave):** Lampu menyala bergantian mengalir secara sekuensial (L1 ➔ L2 ➔ L3) berulang dengan jeda 140ms.
  - **Mode 3 (Dual Hazard Police):** Efek kedip ganda silang dinamis (L1 & L2 blitz 2x, bergantian dengan L3 blitz 2x).
  - **Smart Manual Override:** Menekan saklar lampu manual atau master button akan otomatis mematikan mode animasi dan mengembalikan kontrol ke mode manual.
- **Sinkronisasi Real-Time (Asynchronous Fetch API):** Status lampu diperbarui seketika tanpa perlu memuat ulang (*reload*) halaman, dilengkapi notifikasi melayang (*floating toast feedback*).
- **Proteksi Arus Mandiri:** Setiap LED dilindungi resistor tersendiri (100Ω / 1kΩ) untuk menjaga kestabilan daya dan mencegah LED meredup saat ketiga lampu aktif bersamaan.

---

## 📦 Komponen & Bahan Perakitan

| No | Komponen | Spesifikasi / Keterangan | Jumlah |
|:---:|---|---|:---:|
| 1 | **Mikrokontroler** | NodeMCU ESP-32S (38-Pin v1.1) | 1 unit |
| 2 | **Lampu LED** | LED Diffused 5mm (Merah, Hijau, Kuning, dsb.) | 3 buah |
| 3 | **Resistor Pembatas Arus** | Metal Film (100Ω / 1kΩ) | 3 buah |
| 4 | **Breadboard** | Solderless Breadboard (400 Lubang, 30 Baris) | 1 unit |
| 5 | **Kabel Jumper** | Male-to-Male (Colokan Jarum) | 4 pcs |
| 6 | **Kabel Data** | Micro-USB ke USB-A / Type-C (Daya & Flash) | 1 unit |

---

## 🔌 Skema Pinout & Panduan Titik Breadboard

Pemasangan komponen dirancang rapi pada satu papan breadboard 400 titik:
- **ESP32:** Ditancapkan di bagian atas papan (**Baris 1 sampai 19**).
- **Kolom J (Sisi Kanan ESP32):** Titik colokan sinyal keluaran (GPIO).

| Saluran | Pin ESP32 | Titik Colokan Breadboard | Titik Tujuan Komponen | Fungsi Komponen |
|---|:---:|:---:|:---:|---|
| **Lampu 1 (Ruang Tamu)** | `P2` (GPIO 2) | **Lubang J14** | **Lubang F22** | Kaki Panjang (Anoda +) LED 1 |
| **Lampu 2 (Kamar Tidur)** | `P4` (GPIO 4) | **Lubang J12** | **Lubang F25** | Kaki Panjang (Anoda +) LED 2 |
| **Lampu 3 (Dapur)** | `P5` (GPIO 5) | **Lubang J9** | **Lubang F28** | Kaki Panjang (Anoda +) LED 3 |
| **Resistor Saluran 1** | - | **G23** | **Rel Biru Negatif (-)** | Menahan arus balik LED 1 |
| **Resistor Saluran 2** | - | **G26** | **Rel Biru Negatif (-)** | Menahan arus balik LED 2 |
| **Resistor Saluran 3** | - | **G29** | **Rel Biru Negatif (-)** | Menahan arus balik LED 3 |
| **Ground Utama (GND)** | `GND` | **Lubang J1** | **Rel Biru Negatif (-)** | Jalur pembumian bersama |

> 💡 **Simulasi & Diagram Interaktif:** Buka berkas visual [`docs/wiring.html`](file:///Users/macbookpro/project-dev/kuliah/smart-light-ESP32/docs/wiring.html) pada peramban Anda untuk melihat diagram skematik breadboard animasi.

---

## 🌐 Dokumentasi REST API Endpoints

Server HTTP internal ESP32 menyediakan endpoint RESTful yang mengembalikan data format JSON:

| Method | Endpoint | Fungsi | Respon Contoh |
|:---:|---|---|---|
| `GET` | `/` | Memuat antarmuka Web UI utama | `text/html` (Dashboard) |
| `GET` | `/status` | Mendapatkan status seluruh saluran & mode aktif | `{"l1":false,"l2":true,"l3":false,"mode":0}` |
| `GET` | `/on1` / `/off1` | Menyalakan / mematikan Lampu 1 (GPIO 2) | JSON status terbaru |
| `GET` | `/on2` / `/off2` | Menyalakan / mematikan Lampu 2 (GPIO 4) | JSON status terbaru |
| `GET` | `/on3` / `/off3` | Menyalakan / mematikan Lampu 3 (GPIO 5) | JSON status terbaru |
| `GET` | `/all/on` | Menyalakan ketiga lampu secara serentak | JSON status terbaru |
| `GET` | `/all/off` | Mematikan ketiga lampu secara serentak | JSON status terbaru |
| `GET` | `/mode?val=1` | Mengaktifkan **Mode 1 (Strobo Blitz)** | `{"l1":...,"mode":1}` |
| `GET` | `/mode?val=2` | Mengaktifkan **Mode 2 (Running Wave)** | `{"l1":...,"mode":2}` |
| `GET` | `/mode?val=3` | Mengaktifkan **Mode 3 (Dual Hazard)** | `{"l1":...,"mode":3}` |
| `GET` | `/mode?val=0` | Menonaktifkan animasi (Kembali ke Manual) | `{"l1":...,"mode":0}` |

---

## 🚀 Panduan Upload Firmware (Arduino IDE)

### 1. Persiapan Board ESP32
1. Buka **Arduino IDE** (versi 2.x disarankan).
2. Buka menu **Settings / Preferences** (`Cmd + ,` di macOS atau `Ctrl + ,` di Windows).
3. Tambahkan tautan URL Board Manager ESP32:
   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Masuk ke menu **Boards Manager**, cari `esp32` by **Espressif Systems**, lalu klik **Install**.

### 2. Membuka & Mengunggah Kode
1. Buka berkas [`smart-light-ESP32.ino`](file:///Users/macbookpro/project-dev/kuliah/smart-light-ESP32/smart-light-ESP32.ino) di Arduino IDE.
2. Sambungkan board ESP32 ke laptop menggunakan kabel data USB.
3. Pilih board target: **DOIT ESP32 DEVKIT V1** (atau *ESP32 Dev Module*).
4. Pilih port serial komunikasi yang aktif (contoh: `/dev/cu.usbserial-...` atau `COMx`).
5. Klik tombol **Upload (➔)**.
   *(Jika pada terminal muncul teks `Connecting........_____.....`, tekan dan tahan tombol **BOOT** fisik pada ESP32 selama 1-2 detik hingga proses flashing berjalan).*

---

## 📱 Panduan Pengoperasian dari Smartphone

1. Sambungkan kabel daya ESP32 ke port USB atau charger HP.
2. Pada smartphone Anda, buka pengaturan **Wi-Fi** dan hubungkan ke:
   - **SSID Hotspot:** `ESP32_Smart_Light`
   - **Password:** `12345678`
3. Buka browser (Google Chrome atau Safari), lalu ketikkan alamat:
   ```text
   http://192.168.4.1
   ```
4. **Tips Tampilan Layar Penuh di HP:**
   - Pastikan opsi **"Situs Desktop" / "Desktop site"** pada browser Chrome smartphone Anda **TIDAK DICENTANG**.
   - Halaman akan tampil rapi 100% memenuhi lebar layar ponsel dengan navigasi sentuh yang nyaman.

---

## 📁 Struktur Berkas Proyek

Struktur folder ditata secara modular memisahkan antarmuka, gaya visual, logika klien, dan firmware mikrokontroler:

```text
smart-light-ESP32/
├── smart-light-ESP32.ino   # ⚡ Firmware C++ (Pinout GPIO, Wi-Fi SoftAP, HTTP REST Server)
├── web_ui.h                # 📦 Single-Header Web Bundle (Embedded HTML/CSS/JS via PROGMEM)
├── index.html              # 🌐 Struktur Antarmuka Utama (Semantic HTML5 & Pure SVG Icons)
├── style.css               # 🎨 Desain Sistem Responsif (Plus Jakarta Sans, Fluid Mobile Layout)
├── app.js                  # ⚙️ Logika Kontrol Asinkron, Sinkronisasi REST API, & Toast Controller
├── docs/                   # 📚 Berkas Dokumentasi & Skematik
│   ├── PRD.md              # Product Requirement Document & Naskah Presentasi Video
│   └── wiring.html         # Diagram Breadboard Interaktif 400-Titik
├── assets/                 # 📸 Dokumentasi Foto Fisik Komponen Asli
├── README.md               # 📖 Buku Panduan Utama Proyek
└── .gitignore              # 🛡️ Pengabaian Berkas Sampah Sistem & Build Artifacts
```

---

## ⏱️ Rundown Video Presentasi (Maksimal 5 Menit)

Rancangan alokasi waktu presentasi tugas kuliah:

| Menit & Detik | Segmen Presentasi | Materi yang Dipaparkan |
|:---:|---|---|
| **00:00 - 00:45** | **Pembukaan & Komponen** | • Salam pembuka dan perkenalan identitas mahasiswa/kelompok.<br>• Penjelasan tujuan proyek kendali lampu IoT multi-saluran offline.<br>• Memperlihatkan komponen fisik: ESP32 38-Pin, 3 LED, 3 resistor, dan breadboard. |
| **00:45 - 01:30** | **Skema & Rangkaian Fisik** | • Menunjukkan rangkaian breadboard 400 titik secara close-up.<br>• Menjelaskan pinout: Pin P2, P4, P5 terhubung ke kaki anoda masing-masing LED.<br>• Menjelaskan 3 resistor pembatas arus yang bermuara di rel ground (GND) bersama. |
| **01:30 - 03:15** | **Penjelasan Kode & Arsitektur** | • *Screen recording* Arduino IDE:<br>  - Menjelaskan inisialisasi `WiFi.softAP` mode mandiri tanpa internet.<br>  - Menjelaskan routing REST API (`/on1`, `/status`, `/mode`).<br>  - Menjelaskan fungsi `updateLightingEffects()` berbasis `millis()` non-blocking.<br>  - Menunjukkan struktur antarmuka web modern pada [web_ui.h](file:///Users/macbookpro/project-dev/kuliah/smart-light-ESP32/web_ui.h). |
| **03:15 - 04:30** | **Demo Pengujian via Smartphone** | • Menghubungkan Wi-Fi smartphone ke `ESP32_Smart_Light` ➔ Buka `192.168.4.1`.<br>• Menguji saklar manual satu per satu (Lampu 1, 2, 3 menyala seketika).<br>• Menguji 3 Mode Animasi Dinamis (*Strobo Blitz*, *Running Wave*, *Dual Hazard*).<br>• Menguji tombol master: *Nyalakan Semua* dan *Matikan Semua*. |
| **04:30 - 05:00** | **Kesimpulan & Penutup** | • Ringkasan keunggulan sistem: 100% offline, bebas kuota, respon cepat, dan desain web responsif.<br>• Ucapan terima kasih dan salam penutup. |

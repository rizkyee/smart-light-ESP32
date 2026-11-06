/**
 * Lumina Smart Home - Controller Logic
 * Kontrol lampu ESP32, Mode Animasi Dinamis (Strobo, Running, Hazard), dan REST API
 */

class SmartHomeController {
  constructor() {
    this.states = {
      1: false, // Lampu 1 (Ruang Tamu)
      2: false, // Lampu 2 (Kamar Tidur)
      3: false  // Lampu 3 (Dapur)
    };
    this.currentMode = 0; // 0: Manual, 1: Strobo, 2: Running, 3: Hazard
    this.toastTimer = null;
    this.init();
  }

  init() {
    this.fetchStatus();
    // Sinkronisasi status dari ESP32 setiap 2 detik
    setInterval(() => this.fetchStatus(), 2000);
  }

  /**
   * Menampilkan notifikasi melayang elegan
   */
  showToast(message) {
    const toast = document.getElementById('startupToast');
    const toastMsg = document.getElementById('toastMsg');

    if (!toast || !toastMsg) return;
    toastMsg.innerText = message;

    toast.classList.add('show');
    clearTimeout(this.toastTimer);
    this.toastTimer = setTimeout(() => {
      toast.classList.remove('show');
    }, 2200);
  }

  /**
   * Update status UI saklar lampu manual
   */
  updateDeviceUI(id, isOn) {
    this.states[id] = isOn;
    const row = document.getElementById(`deviceRow${id}`);
    const toggle = document.getElementById(`switch${id}`);
    const statusLabel = document.getElementById(`statusLabel${id}`);

    if (toggle) toggle.checked = isOn;

    if (row) {
      if (isOn) {
        row.classList.add('active');
      } else {
        row.classList.remove('active');
      }
    }

    if (statusLabel) {
      statusLabel.innerText = isOn ? 'Menyala' : 'Mati';
    }
  }

  /**
   * Update visual kartu mode animasi (Strobo, Running, Hazard)
   */
  updateModeUI(mode) {
    this.currentMode = mode;
    for (let i = 1; i <= 3; i++) {
      const card = document.getElementById(`modeCard${i}`);
      if (card) {
        if (mode === i) {
          card.classList.add('active');
        } else {
          card.classList.remove('active');
        }
      }
    }
    this.updateOverview();
  }

  /**
   * Update kartu ringkasan status utama
   */
  updateOverview() {
    const activeCount = Object.values(this.states).filter(Boolean).length;
    const overviewCard = document.getElementById('overviewCard');
    const metricNum = document.getElementById('metricNum');
    const overviewTitle = document.getElementById('overviewTitle');
    const overviewDesc = document.getElementById('overviewDesc');

    if (this.currentMode > 0) {
      // Tampilan jika mode efek sedang berjalan
      const modeNames = {
        1: 'Mode Strobo Blitz Aktif',
        2: 'Mode Running Wave Aktif',
        3: 'Mode Dual Hazard Aktif'
      };
      const modeDescs = {
        1: 'Semua lampu berkedip frekuensi tinggi',
        2: 'Lampu bergiliran berurutan 1 - 2 - 3',
        3: 'Kedip ganda silang ala hazard patroli'
      };

      if (overviewTitle) overviewTitle.innerText = modeNames[this.currentMode];
      if (overviewDesc) overviewDesc.innerText = modeDescs[this.currentMode];
      if (metricNum) metricNum.innerText = 'Mode Efek';
      if (overviewCard) overviewCard.classList.add('has-active');
      return;
    }

    // Tampilan mode manual biasa
    if (metricNum) metricNum.innerText = `${activeCount} / 3 Aktif`;

    if (overviewCard) {
      if (activeCount > 0) {
        overviewCard.classList.add('has-active');
      } else {
        overviewCard.classList.remove('has-active');
      }
    }

    if (overviewTitle && overviewDesc) {
      if (activeCount === 0) {
        overviewTitle.innerText = 'Semua Lampu Padam';
        overviewDesc.innerText = 'Sistem standby dalam mode hemat daya';
      } else if (activeCount === 3) {
        overviewTitle.innerText = 'Seluruh Ruangan Terang';
        overviewDesc.innerText = '3 lampu saluran aktif bersamaan';
      } else {
        overviewTitle.innerText = `${activeCount} Lampu Sedang Aktif`;
        overviewDesc.innerText = 'Kendali lokal nirkabel ESP32';
      }
    }
  }

  /**
   * Toggle Lampu Manual Individu
   */
  async toggleDevice(id, explicitState = null) {
    const nextState = explicitState !== null ? explicitState : !this.states[id];
    const roomNames = { 1: 'Ruang Tamu', 2: 'Kamar Tidur', 3: 'Dapur' };

    // Menonaktifkan mode efek jika lampu manual ditekan
    this.updateModeUI(0);
    this.updateDeviceUI(id, nextState);
    this.updateOverview();
    this.showToast(`Lampu ${roomNames[id]} ${nextState ? 'dinyalakan' : 'dimatikan'}`);

    const endpoint = nextState ? `/on${id}` : `/off${id}`;
    try {
      const res = await fetch(endpoint);
      if (res.ok) {
        const data = await res.json();
        this.applyServerState(data);
      }
    } catch (err) {
      console.log(`[Offline Mode] Toggle Lampu ${id} -> ${nextState}`);
    }
  }

  /**
   * Master Control: Semua ON / Semua OFF
   */
  async setMaster(turnOn) {
    this.updateModeUI(0);
    this.updateDeviceUI(1, turnOn);
    this.updateDeviceUI(2, turnOn);
    this.updateDeviceUI(3, turnOn);
    this.updateOverview();

    this.showToast(turnOn ? 'Seluruh lampu dinyalakan' : 'Seluruh lampu dimatikan');

    const endpoint = turnOn ? '/all/on' : '/all/off';
    try {
      const res = await fetch(endpoint);
      if (res.ok) {
        const data = await res.json();
        this.applyServerState(data);
      }
    } catch (err) {
      console.log(`[Offline Mode] Set Master -> ${turnOn}`);
    }
  }

  /**
   * Toggle Efek Animasi Dinamis (Mode 1: Strobo, Mode 2: Running, Mode 3: Hazard)
   */
  async toggleMode(modeNum) {
    // Jika mode yang sama ditekan lagi, matikan efek kembali ke 0
    const targetMode = (this.currentMode === modeNum) ? 0 : modeNum;
    this.updateModeUI(targetMode);

    const modeLabels = {
      0: 'Efek dinonaktifkan (Manual)',
      1: 'Mode Strobo Blitz Aktif',
      2: 'Mode Running Wave Aktif',
      3: 'Mode Dual Hazard Aktif'
    };
    this.showToast(modeLabels[targetMode]);

    try {
      const res = await fetch(`/mode?val=${targetMode}`);
      if (res.ok) {
        const data = await res.json();
        this.applyServerState(data);
      }
    } catch (err) {
      console.log(`[Offline Mode] Set Mode -> ${targetMode}`);
    }
  }

  /**
   * Terapkan data JSON dari ESP32
   */
  applyServerState(data) {
    if (typeof data.l1 === 'boolean') this.updateDeviceUI(1, data.l1);
    if (typeof data.l2 === 'boolean') this.updateDeviceUI(2, data.l2);
    if (typeof data.l3 === 'boolean') this.updateDeviceUI(3, data.l3);
    if (typeof data.mode === 'number') this.updateModeUI(data.mode);
    this.updateOverview();
  }

  /**
   * Ambil status terbaru dari REST API (/status)
   */
  async fetchStatus() {
    try {
      const res = await fetch('/status');
      if (res.ok) {
        const data = await res.json();
        this.applyServerState(data);
      }
    } catch (err) {
      this.updateOverview();
    }
  }
}

// Inisialisasi saat DOM siap
document.addEventListener('DOMContentLoaded', () => {
  window.app = new SmartHomeController();
});

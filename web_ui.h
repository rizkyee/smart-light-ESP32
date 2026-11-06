#ifndef WEB_UI_H
#define WEB_UI_H

#include <pgmspace.h>

// ============================================================================
// Lumina Smart Home - Modern Startup Design System
// Font: Plus Jakarta Sans & Inter • 3 Mode Animasi • 100% Fluid Responsive
// ============================================================================

const char HTML_PAGE[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, viewport-fit=cover">
  <title>Lumina IoT - Smart Light Controller</title>
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Plus+Jakarta+Sans:wght@400;500;600;700;800&family=Inter:wght@400;500;600;700&display=swap" rel="stylesheet">
  <style>
    @import url('https://fonts.googleapis.com/css2?family=Plus+Jakarta+Sans:wght@400;500;600;700;800&family=Inter:wght@400;500;600;700&display=swap');
    :root {
      --bg-page: #f8fafc;
      --bg-card: #ffffff;
      --bg-card-hover: #fafbfc;
      --bg-muted: #f1f5f9;
      --border-card: #e2e8f0;
      --border-focus: #cbd5e1;
      --text-title: #0f172a;
      --text-body: #334155;
      --text-muted: #64748b;
      --text-sub: #94a3b8;
      --emerald-primary: #10b981;
      --emerald-hover: #059669;
      --emerald-soft: #ecfdf5;
      --emerald-border: rgba(16, 185, 129, 0.3);
      --emerald-glow: rgba(16, 185, 129, 0.2);
      --amber-primary: #f59e0b;
      --amber-soft: #fffbeb;
      --amber-border: rgba(245, 158, 11, 0.3);
      --amber-glow: rgba(245, 158, 11, 0.22);
      --blue-primary: #0284c7;
      --blue-soft: #f0f9ff;
      --blue-border: rgba(2, 132, 199, 0.3);
      --blue-glow: rgba(2, 132, 199, 0.2);
      --dark-primary: #0f172a;
      --dark-hover: #1e293b;
      --shadow-sm: 0 1px 2px 0 rgba(0, 0, 0, 0.05);
      --shadow-card: 0 2px 8px -2px rgba(15, 23, 42, 0.05), 0 1px 3px rgba(15, 23, 42, 0.03);
      --shadow-card-hover: 0 8px 20px -4px rgba(15, 23, 42, 0.08);
      --radius-card: 18px;
      --radius-squircle: 13px;
      --radius-pill: 9999px;
      --transition-fast: all 0.22s cubic-bezier(0.16, 1, 0.3, 1);
    }
    *, *::before, *::after {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      -webkit-tap-highlight-color: transparent;
      user-select: none;
      font-family: 'Plus Jakarta Sans', 'Inter', -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
    }
    html {
      width: 100%;
      height: 100%;
      margin: 0;
      padding: 0;
      background-color: var(--bg-page);
    }
    body {
      width: 100%;
      min-height: 100vh;
      min-height: 100dvh;
      margin: 0;
      padding: 0;
      background-color: var(--bg-page);
      color: var(--text-title);
      display: flex;
      justify-content: center;
      align-items: flex-start;
      -webkit-font-smoothing: antialiased;
      -moz-osx-font-smoothing: grayscale;
    }
    .startup-container {
      width: 100%;
      max-width: 520px;
      margin: 0 auto;
      padding: 16px 16px 48px;
      display: flex;
      flex-direction: column;
      gap: 14px;
    }
    .startup-header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      padding: 4px 2px;
    }
    .brand-section {
      display: flex;
      align-items: center;
      gap: 12px;
    }
    .brand-icon-box {
      width: 44px;
      height: 44px;
      border-radius: var(--radius-squircle);
      background: linear-gradient(135deg, #0f172a 0%, #334155 100%);
      display: flex;
      align-items: center;
      justify-content: center;
      color: #ffffff;
      box-shadow: 0 4px 14px -2px rgba(15, 23, 42, 0.25);
      flex-shrink: 0;
    }
    .brand-info h1 {
      font-size: 20px;
      font-weight: 800;
      letter-spacing: -0.4px;
      color: var(--text-title);
      line-height: 1.2;
    }
    .brand-info p {
      font-size: 12px;
      color: var(--text-muted);
      font-weight: 500;
      margin-top: 1px;
    }
    .network-badge {
      display: inline-flex;
      align-items: center;
      gap: 6px;
      background-color: var(--bg-card);
      border: 1px solid var(--border-card);
      padding: 6px 12px;
      border-radius: var(--radius-pill);
      font-size: 11.5px;
      font-weight: 600;
      color: var(--text-body);
      box-shadow: var(--shadow-sm);
      white-space: nowrap;
    }
    .status-dot-pulse {
      width: 7px;
      height: 7px;
      border-radius: 50%;
      background-color: var(--emerald-primary);
      animation: pulse-dot 2s infinite cubic-bezier(0.45, 0, 0.2, 1);
    }
    @keyframes pulse-dot {
      0% { transform: scale(0.95); box-shadow: 0 0 0 0 rgba(16, 185, 129, 0.6); }
      70% { transform: scale(1); box-shadow: 0 0 0 6px rgba(16, 185, 129, 0); }
      100% { transform: scale(0.95); box-shadow: 0 0 0 0 rgba(16, 185, 129, 0); }
    }
    .overview-card {
      background-color: var(--bg-card);
      border: 1px solid var(--border-card);
      border-radius: var(--radius-card);
      padding: 18px 20px;
      display: flex;
      justify-content: space-between;
      align-items: center;
      gap: 14px;
      box-shadow: var(--shadow-card);
      transition: var(--transition-fast);
    }
    .overview-text {
      flex: 1;
      min-width: 0;
    }
    .overview-text h2 {
      font-size: 15.5px;
      font-weight: 700;
      letter-spacing: -0.2px;
      color: var(--text-title);
      margin-bottom: 3px;
      white-space: nowrap;
      overflow: hidden;
      text-overflow: ellipsis;
    }
    .overview-text p {
      font-size: 12px;
      color: var(--text-muted);
      line-height: 1.35;
    }
    .metric-pill {
      display: inline-flex;
      align-items: center;
      gap: 7px;
      background: var(--bg-muted);
      border: 1px solid var(--border-card);
      padding: 8px 14px;
      border-radius: var(--radius-pill);
      color: var(--text-body);
      white-space: nowrap;
      flex-shrink: 0;
      transition: var(--transition-fast);
    }
    .overview-card.has-active .metric-pill {
      background: var(--amber-soft);
      border-color: var(--amber-border);
      color: #b45309;
    }
    .metric-icon { display: flex; align-items: center; }
    .metric-num { font-size: 13px; font-weight: 700; letter-spacing: -0.1px; }
    .section-headline {
      font-size: 11.5px;
      font-weight: 700;
      text-transform: uppercase;
      letter-spacing: 0.6px;
      color: var(--text-muted);
      padding: 4px 2px 0;
    }
    .device-stack {
      display: flex;
      flex-direction: column;
      gap: 10px;
    }
    .device-row {
      background-color: var(--bg-card);
      border: 1.5px solid var(--border-card);
      border-radius: var(--radius-card);
      padding: 16px 18px;
      display: flex;
      align-items: center;
      justify-content: space-between;
      box-shadow: var(--shadow-card);
      cursor: pointer;
      transition: var(--transition-fast);
    }
    .device-row:hover {
      border-color: var(--border-focus);
      box-shadow: var(--shadow-card-hover);
    }
    .device-row:active { transform: scale(0.985); }
    .device-row.active {
      background-color: #ffffff;
      border-color: rgba(245, 158, 11, 0.45);
      box-shadow: 0 4px 18px -2px rgba(245, 158, 11, 0.16);
    }
    .device-row.chan-2.active {
      border-color: rgba(2, 132, 199, 0.45);
      box-shadow: 0 4px 18px -2px rgba(2, 132, 199, 0.16);
    }
    .device-row.chan-3.active {
      border-color: rgba(16, 185, 129, 0.45);
      box-shadow: 0 4px 18px -2px rgba(16, 185, 129, 0.16);
    }
    .device-left {
      display: flex;
      align-items: center;
      gap: 14px;
    }
    .device-squircle {
      width: 46px;
      height: 46px;
      border-radius: var(--radius-squircle);
      background-color: var(--bg-muted);
      display: flex;
      align-items: center;
      justify-content: center;
      color: var(--text-sub);
      transition: var(--transition-fast);
      flex-shrink: 0;
    }
    .device-row.active .device-squircle {
      background: var(--amber-soft);
      color: var(--amber-primary);
      box-shadow: 0 0 16px var(--amber-glow);
    }
    .device-row.chan-2.active .device-squircle {
      background: var(--blue-soft);
      color: var(--blue-primary);
      box-shadow: 0 0 16px var(--blue-glow);
    }
    .device-row.chan-3.active .device-squircle {
      background: var(--emerald-soft);
      color: var(--emerald-primary);
      box-shadow: 0 0 16px var(--emerald-glow);
    }
    .device-meta { display: flex; flex-direction: column; }
    .room-chip {
      font-size: 10.5px;
      font-weight: 700;
      text-transform: uppercase;
      letter-spacing: 0.5px;
      color: var(--text-muted);
      margin-bottom: 2px;
    }
    .device-name {
      font-size: 16px;
      font-weight: 700;
      color: var(--text-title);
      letter-spacing: -0.2px;
    }
    .device-sub {
      font-size: 12px;
      color: var(--text-muted);
      margin-top: 3px;
      display: flex;
      align-items: center;
      gap: 6px;
    }
    .status-dot-mini {
      width: 6px;
      height: 6px;
      border-radius: 50%;
      background-color: #cbd5e1;
      transition: var(--transition-fast);
    }
    .device-row.active .status-dot-mini { background-color: var(--emerald-primary); }
    .device-row.active .status-label { color: var(--emerald-primary); font-weight: 700; }
    .device-right { display: flex; align-items: center; flex-shrink: 0; }
    .switch-control {
      position: relative;
      display: inline-block;
      width: 50px;
      height: 30px;
      cursor: pointer;
    }
    .switch-control input { opacity: 0; width: 0; height: 0; }
    .switch-slider {
      position: absolute;
      top: 0; left: 0; right: 0; bottom: 0;
      background-color: #cbd5e1;
      border-radius: var(--radius-pill);
      transition: all 0.28s cubic-bezier(0.4, 0, 0.2, 1);
    }
    .switch-slider::before {
      position: absolute;
      content: "";
      height: 24px;
      width: 24px;
      left: 3px;
      bottom: 3px;
      background-color: #ffffff;
      border-radius: 50%;
      transition: all 0.28s cubic-bezier(0.4, 0, 0.2, 1);
      box-shadow: 0 2px 5px rgba(0, 0, 0, 0.16);
    }
    .switch-control input:checked + .switch-slider { background-color: var(--emerald-primary); }
    .switch-control input:checked + .switch-slider::before { transform: translateX(20px); }
    .modes-grid {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 10px;
    }
    .mode-card {
      background-color: var(--bg-card);
      border: 1.5px solid var(--border-card);
      border-radius: var(--radius-card);
      padding: 14px 10px;
      display: flex;
      flex-direction: column;
      align-items: center;
      text-align: center;
      gap: 8px;
      cursor: pointer;
      transition: var(--transition-fast);
      box-shadow: var(--shadow-sm);
      position: relative;
      overflow: hidden;
    }
    .mode-card:hover {
      border-color: var(--border-focus);
      box-shadow: var(--shadow-card-hover);
    }
    .mode-card:active { transform: scale(0.96); }
    .mode-card.active {
      background-color: #ffffff;
      border-color: var(--amber-primary);
      box-shadow: 0 4px 16px -2px rgba(245, 158, 11, 0.28);
    }
    .mode-card.active::before {
      content: '';
      position: absolute;
      top: 0; left: 0; right: 0;
      height: 3px;
      background: linear-gradient(90deg, #f59e0b, #10b981);
    }
    .mode-icon-box {
      width: 38px;
      height: 38px;
      border-radius: var(--radius-squircle);
      background-color: var(--bg-muted);
      display: flex;
      align-items: center;
      justify-content: center;
      color: var(--text-muted);
      transition: var(--transition-fast);
    }
    .mode-card.active .mode-icon-box {
      background-color: var(--amber-soft);
      color: var(--amber-primary);
      box-shadow: 0 0 12px var(--amber-glow);
      transform: scale(1.06);
    }
    .mode-info { display: flex; flex-direction: column; gap: 2px; }
    .mode-name {
      font-size: 13px;
      font-weight: 700;
      color: var(--text-title);
      letter-spacing: -0.2px;
      line-height: 1.2;
    }
    .mode-sub { font-size: 10px; color: var(--text-muted); font-weight: 600; }
    .mode-card.active .mode-name { color: #b45309; }
    .actions-grid {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 12px;
      margin-top: 4px;
    }
    .btn-master {
      border: none;
      border-radius: 14px;
      padding: 15px 16px;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 8px;
      font-size: 14px;
      font-weight: 700;
      cursor: pointer;
      transition: var(--transition-fast);
      box-shadow: var(--shadow-sm);
    }
    .btn-master:active { transform: scale(0.96); }
    .btn-master.btn-on { background-color: var(--emerald-primary); color: #ffffff; }
    .btn-master.btn-on:hover { background-color: var(--emerald-hover); }
    .btn-master.btn-off { background-color: var(--dark-primary); color: #ffffff; }
    .btn-master.btn-off:hover { background-color: var(--dark-hover); }
    .specs-card {
      background-color: var(--bg-card);
      border: 1px solid var(--border-card);
      border-radius: var(--radius-card);
      padding: 16px 18px;
      display: flex;
      flex-direction: column;
      gap: 11px;
      font-size: 12.5px;
      color: var(--text-muted);
      box-shadow: var(--shadow-sm);
      margin-top: 4px;
    }
    .specs-item {
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
    .specs-key {
      display: flex;
      align-items: center;
      gap: 8px;
      color: var(--text-muted);
      font-weight: 500;
    }
    .specs-val { color: var(--text-title); font-weight: 700; }
    .startup-toast {
      position: fixed;
      top: 24px;
      left: 50%;
      transform: translateX(-50%) translateY(-100px);
      background-color: rgba(15, 23, 42, 0.94);
      backdrop-filter: blur(10px);
      -webkit-backdrop-filter: blur(10px);
      color: #ffffff;
      padding: 10px 18px;
      border-radius: var(--radius-pill);
      font-size: 12.5px;
      font-weight: 600;
      display: flex;
      align-items: center;
      gap: 8px;
      z-index: 100;
      opacity: 0;
      transition: all 0.3s cubic-bezier(0.16, 1, 0.3, 1);
      box-shadow: 0 10px 25px rgba(0, 0, 0, 0.2);
      pointer-events: none;
      white-space: nowrap;
    }
    .startup-toast.show { transform: translateX(-50%) translateY(0); opacity: 1; }
    .toast-svg { display: flex; align-items: center; color: #38bdf8; }
    @media (max-width: 400px) {
      .startup-container { padding: 12px 12px 40px; gap: 12px; }
      .device-row { padding: 14px 14px; }
      .modes-grid { gap: 8px; }
      .mode-card { padding: 12px 6px; }
      .mode-name { font-size: 12px; }
      .mode-sub { font-size: 9px; }
    }
  </style>
</head>
<body>

  <!-- Floating Toast Notification -->
  <div class="startup-toast" id="startupToast">
    <span class="toast-svg">
      <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round">
        <polyline points="20 6 9 17 4 12"/>
      </svg>
    </span>
    <span id="toastMsg">Perangkat diperbarui</span>
  </div>

  <!-- Single-Page Centered Application Hub -->
  <main class="startup-container">

    <!-- 1. Header Startup Identity -->
    <header class="startup-header">
      <div class="brand-section">
        <div class="brand-icon-box">
          <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round">
            <path d="M3 9l9-7 9 7v11a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"/>
            <polyline points="9 22 9 12 15 12 15 22"/>
          </svg>
        </div>
        <div class="brand-info">
          <h1>Rumah Pintar</h1>
          <p>ESP32 IoT Controller</p>
        </div>
      </div>

      <div class="network-badge">
        <span class="status-dot-pulse"></span>
        <span>192.168.4.1</span>
      </div>
    </header>

    <!-- 2. Overview Metric Banner (Rapi & Seimbang) -->
    <section class="overview-card" id="overviewCard">
      <div class="overview-text">
        <h2 id="overviewTitle">Semua Lampu Padam</h2>
        <p id="overviewDesc">Sistem standby dalam mode hemat daya</p>
      </div>

      <div class="metric-pill">
        <span class="metric-icon">
          <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round">
            <path d="M9 18h6"/><path d="M10 22h4"/>
            <path d="M15.09 14c.18-.98.65-1.74 1.41-2.5A4.65 4.65 0 0 0 18 8 6 6 0 0 0 6 8c0 1 .23 2.23 1.5 3.5A4.61 4.61 0 0 1 8.91 14"/>
          </svg>
        </span>
        <span class="metric-num" id="metricNum">0 / 3 Aktif</span>
      </div>
    </section>

    <!-- 3. Katalog Perangkat Lampu (3 Saluran) -->
    <section>
      <div class="section-headline">Katalog Perangkat (3 Saluran)</div>

      <div class="device-stack">
        <!-- Saluran 1: Ruang Tamu -->
        <article class="device-row chan-1" id="deviceRow1" onclick="window.app.toggleDevice(1)">
          <div class="device-left">
            <div class="device-squircle">
              <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M9 18h6"/><path d="M10 22h4"/>
                <path d="M15.09 14c.18-.98.65-1.74 1.41-2.5A4.65 4.65 0 0 0 18 8 6 6 0 0 0 6 8c0 1 .23 2.23 1.5 3.5A4.61 4.61 0 0 1 8.91 14"/>
              </svg>
            </div>
            <div class="device-meta">
              <span class="room-chip">Ruang Tamu</span>
              <h3 class="device-name">Lampu Utama</h3>
              <div class="device-sub">
                <span class="status-dot-mini"></span>
                <span class="status-label" id="statusLabel1">Mati</span>
              </div>
            </div>
          </div>

          <div class="device-right">
            <label class="switch-control" onclick="event.stopPropagation()">
              <input type="checkbox" id="switch1" onchange="window.app.toggleDevice(1, this.checked)">
              <span class="switch-slider"></span>
            </label>
          </div>
        </article>

        <!-- Saluran 2: Kamar Tidur -->
        <article class="device-row chan-2" id="deviceRow2" onclick="window.app.toggleDevice(2)">
          <div class="device-left">
            <div class="device-squircle">
              <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M12 2v8"/><path d="m4.93 10.93 1.41 1.41"/><path d="M2 18h20"/>
                <path d="M20 18v2a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2v-2"/><path d="m19.07 10.93-1.41 1.41"/>
                <path d="M12 6a4 4 0 0 0-4 4v8h8v-8a4 4 0 0 0-4-4Z"/>
              </svg>
            </div>
            <div class="device-meta">
              <span class="room-chip">Kamar Tidur</span>
              <h3 class="device-name">Lampu Tidur</h3>
              <div class="device-sub">
                <span class="status-dot-mini"></span>
                <span class="status-label" id="statusLabel2">Mati</span>
              </div>
            </div>
          </div>

          <div class="device-right">
            <label class="switch-control" onclick="event.stopPropagation()">
              <input type="checkbox" id="switch2" onchange="window.app.toggleDevice(2, this.checked)">
              <span class="switch-slider"></span>
            </label>
          </div>
        </article>

        <!-- Saluran 3: Dapur -->
        <article class="device-row chan-3" id="deviceRow3" onclick="window.app.toggleDevice(3)">
          <div class="device-left">
            <div class="device-squircle">
              <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <line x1="12" y1="2" x2="12" y2="7"/>
                <path d="M6 14h12l-2-7H8l-2 7z"/>
                <path d="M9 18h6"/><path d="M10 21h4"/>
              </svg>
            </div>
            <div class="device-meta">
              <span class="room-chip">Dapur & Makan</span>
              <h3 class="device-name">Lampu Dapur</h3>
              <div class="device-sub">
                <span class="status-dot-mini"></span>
                <span class="status-label" id="statusLabel3">Mati</span>
              </div>
            </div>
          </div>

          <div class="device-right">
            <label class="switch-control" onclick="event.stopPropagation()">
              <input type="checkbox" id="switch3" onchange="window.app.toggleDevice(3, this.checked)">
              <span class="switch-slider"></span>
            </label>
          </div>
        </article>
      </div>
    </section>

    <!-- 4. Mode Animasi Dinamis (3 Mode) -->
    <section>
      <div class="section-headline">Efek Animasi Dinamis</div>
      <div class="modes-grid">
        <!-- Mode 1: Strobo Blitz -->
        <button class="mode-card" id="modeCard1" onclick="window.app.toggleMode(1)">
          <div class="mode-icon-box">
            <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round">
              <polygon points="13 2 3 14 12 14 11 22 21 10 12 10 13 2"/>
            </svg>
          </div>
          <div class="mode-info">
            <span class="mode-name">Strobo Blitz</span>
            <span class="mode-sub">Kedip Cepat</span>
          </div>
        </button>

        <!-- Mode 2: Running Wave -->
        <button class="mode-card" id="modeCard2" onclick="window.app.toggleMode(2)">
          <div class="mode-icon-box">
            <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round">
              <polyline points="13 17 18 12 13 7"/>
              <polyline points="6 17 11 12 6 7"/>
            </svg>
          </div>
          <div class="mode-info">
            <span class="mode-name">Running Wave</span>
            <span class="mode-sub">Jalan 1-2-3</span>
          </div>
        </button>

        <!-- Mode 3: Dual Hazard -->
        <button class="mode-card" id="modeCard3" onclick="window.app.toggleMode(3)">
          <div class="mode-icon-box">
            <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round">
              <circle cx="12" cy="12" r="9"/>
              <line x1="12" y1="8" x2="12" y2="12"/>
              <line x1="12" y1="16" x2="12.01" y2="16"/>
            </svg>
          </div>
          <div class="mode-info">
            <span class="mode-name">Dual Hazard</span>
            <span class="mode-sub">Kedip Silang</span>
          </div>
        </button>
      </div>
    </section>

    <!-- 5. Kontrol Serentak (Side-by-Side) -->
    <section>
      <div class="section-headline">Kontrol Serentak</div>
      <div class="actions-grid">
        <button class="btn-master btn-on" onclick="window.app.setMaster(true)">
          <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round">
            <circle cx="12" cy="12" r="4"/><path d="M12 2v2"/><path d="M12 20v2"/><path d="m4.93 4.93 1.41 1.41"/><path d="m17.66 17.66 1.41 1.41"/><path d="M2 12h2"/><path d="M20 12h2"/><path d="m6.34 17.66-1.41 1.41"/><path d="m19.07 4.93-1.41 1.41"/>
          </svg>
          <span>Nyalakan Semua</span>
        </button>

        <button class="btn-master btn-off" onclick="window.app.setMaster(false)">
          <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round">
            <path d="M12 2v10"/><path d="M18.4 6.6a9 9 0 1 1-12.77.04"/>
          </svg>
          <span>Matikan Semua</span>
        </button>
      </div>
    </section>

    <!-- 6. Spesifikasi Hardware Card -->
    <section class="specs-card">
      <div class="specs-item">
        <span class="specs-key">
          <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
            <rect width="18" height="18" x="3" y="3" rx="2"/><path d="M9 9h6v6H9z"/><path d="M3 9h2"/><path d="M3 15h2"/><path d="M21 9h-2"/><path d="M21 15h-2"/><path d="M9 3v2"/><path d="M15 3v2"/><path d="M9 21v-2"/><path d="M15 21v-2"/>
          </svg>
          <span>Mikrokontroler</span>
        </span>
        <span class="specs-val">NodeMCU ESP-32S (38-Pin)</span>
      </div>

      <div class="specs-item">
        <span class="specs-key">
          <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
            <path d="M5 12.55a11 11 0 0 1 14.08 0"/><path d="M1.42 9a16 16 0 0 1 21.16 0"/><path d="M8.53 16.11a6 6 0 0 1 6.95 0"/><line x1="12" y1="20" x2="12.01" y2="20"/>
          </svg>
          <span>Konektivitas</span>
        </span>
        <span class="specs-val">Wi-Fi Access Point (Offline)</span>
      </div>

      <div class="specs-item">
        <span class="specs-key">
          <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
            <rect width="20" height="8" x="2" y="2" rx="2" ry="2"/><rect width="20" height="8" x="2" y="14" rx="2" ry="2"/><line x1="6" y1="6" x2="6.01" y2="6"/><line x1="6" y1="18" x2="6.01" y2="18"/>
          </svg>
          <span>Protokol Jaringan</span>
        </span>
        <span class="specs-val">HTTP REST Server (Port 80)</span>
      </div>
    </section>

  </main>

  <script>
    class SmartHomeController {
      constructor() {
        this.states = { 1: false, 2: false, 3: false };
        this.currentMode = 0;
        this.toastTimer = null;
        this.init();
      }

      init() {
        this.fetchStatus();
        setInterval(() => this.fetchStatus(), 2000);
      }

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

      updateDeviceUI(id, isOn) {
        this.states[id] = isOn;
        const row = document.getElementById('deviceRow' + id);
        const toggle = document.getElementById('switch' + id);
        const statusLabel = document.getElementById('statusLabel' + id);

        if (toggle) toggle.checked = isOn;
        if (row) {
          if (isOn) row.classList.add('active');
          else row.classList.remove('active');
        }
        if (statusLabel) statusLabel.innerText = isOn ? 'Menyala' : 'Mati';
      }

      updateModeUI(mode) {
        this.currentMode = mode;
        for (let i = 1; i <= 3; i++) {
          const card = document.getElementById('modeCard' + i);
          if (card) {
            if (mode === i) card.classList.add('active');
            else card.classList.remove('active');
          }
        }
        this.updateOverview();
      }

      updateOverview() {
        const activeCount = Object.values(this.states).filter(Boolean).length;
        const overviewCard = document.getElementById('overviewCard');
        const metricNum = document.getElementById('metricNum');
        const overviewTitle = document.getElementById('overviewTitle');
        const overviewDesc = document.getElementById('overviewDesc');

        if (this.currentMode > 0) {
          const modeNames = { 1: 'Mode Strobo Blitz Aktif', 2: 'Mode Running Wave Aktif', 3: 'Mode Dual Hazard Aktif' };
          const modeDescs = { 1: 'Semua lampu berkedip frekuensi tinggi', 2: 'Lampu bergiliran berurutan 1 - 2 - 3', 3: 'Kedip ganda silang ala hazard patroli' };

          if (overviewTitle) overviewTitle.innerText = modeNames[this.currentMode];
          if (overviewDesc) overviewDesc.innerText = modeDescs[this.currentMode];
          if (metricNum) metricNum.innerText = 'Mode Efek';
          if (overviewCard) overviewCard.classList.add('has-active');
          return;
        }

        if (metricNum) metricNum.innerText = activeCount + ' / 3 Aktif';
        if (overviewCard) {
          if (activeCount > 0) overviewCard.classList.add('has-active');
          else overviewCard.classList.remove('has-active');
        }
        if (overviewTitle && overviewDesc) {
          if (activeCount === 0) {
            overviewTitle.innerText = 'Semua Lampu Padam';
            overviewDesc.innerText = 'Sistem standby dalam mode hemat daya';
          } else if (activeCount === 3) {
            overviewTitle.innerText = 'Seluruh Ruangan Terang';
            overviewDesc.innerText = '3 lampu saluran aktif bersamaan';
          } else {
            overviewTitle.innerText = activeCount + ' Lampu Sedang Aktif';
            overviewDesc.innerText = 'Kendali lokal nirkabel ESP32';
          }
        }
      }

      async toggleDevice(id, explicitState = null) {
        const nextState = explicitState !== null ? explicitState : !this.states[id];
        const roomNames = { 1: 'Ruang Tamu', 2: 'Kamar Tidur', 3: 'Dapur' };

        this.updateModeUI(0);
        this.updateDeviceUI(id, nextState);
        this.updateOverview();
        this.showToast('Lampu ' + roomNames[id] + ' ' + (nextState ? 'dinyalakan' : 'dimatikan'));

        const endpoint = nextState ? ('/on' + id) : ('/off' + id);
        try {
          const res = await fetch(endpoint);
          if (res.ok) {
            const data = await res.json();
            this.applyServerState(data);
          }
        } catch (err) {}
      }

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
        } catch (err) {}
      }

      async toggleMode(modeNum) {
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
          const res = await fetch('/mode?val=' + targetMode);
          if (res.ok) {
            const data = await res.json();
            this.applyServerState(data);
          }
        } catch (err) {}
      }

      applyServerState(data) {
        if (typeof data.l1 === 'boolean') this.updateDeviceUI(1, data.l1);
        if (typeof data.l2 === 'boolean') this.updateDeviceUI(2, data.l2);
        if (typeof data.l3 === 'boolean') this.updateDeviceUI(3, data.l3);
        if (typeof data.mode === 'number') this.updateModeUI(data.mode);
        this.updateOverview();
      }

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

    document.addEventListener('DOMContentLoaded', () => {
      window.app = new SmartHomeController();
    });
  </script>
</body>
</html>)rawliteral";

#endif // WEB_UI_H

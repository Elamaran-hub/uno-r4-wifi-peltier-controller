# ❄️ UNO R4 WiFi — Peltier Temperature Control System

> A WiFi-controlled thermal management system using Arduino UNO R4 WiFi, MOSFET-based PWM switching, DS18B20 temperature sensing, and a mobile-accessible web interface — no router required.

![Status](https://img.shields.io/badge/Status-Completed-3fb950?style=flat-square)
![Platform](https://img.shields.io/badge/Platform-Arduino%20UNO%20R4%20WiFi-00979D?style=flat-square)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20(Arduino)-blue?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-f0a500?style=flat-square)
![Interface](https://img.shields.io/badge/Interface-WiFi%20Web%20UI-purple?style=flat-square)

---

## 📌 Overview

This project demonstrates a complete **closed-loop thermal control system** built around the **Arduino UNO R4 WiFi**. It controls a 12V Peltier (TEC) module using **MOSFET-based PWM**, measures temperature via a **DS18B20 digital sensor**, and provides real-time monitoring and control through:

- A **16×2 I2C LCD** for local display
- A **WiFi Access Point web interface** accessible from any smartphone — no router needed

**Use cases:** Wearable cooling systems, portable cold pads, mini refrigeration prototypes, temperature-stabilised electronics enclosures, and medical cold therapy devices.

---

## 🧠 System Architecture

```
📱 Phone (Web UI)
       │
       │  WiFi (AP Mode — no router needed)
       ▼
┌─────────────────────┐
│  Arduino UNO R4 WiFi │ ◄── DS18B20 Temp Sensor (Pin 2)
│  (192.168.4.1)      │ ──► I2C LCD 16×2 (SDA/SCL)
│  PWM Output → D9   │ ──► MOSFET Gate
└─────────────────────┘
                              │
                       ┌──────┴──────┐
                       │   N-Channel  │
                       │    MOSFET    │  ◄── 12V Supply
                       │ IRFZ44N/     │
                       │ IRF44N       │
                       └──────┬──────┘
                              │
                       ┌──────┴──────┐
                       │  TEC1-12706  │
                       │   Peltier    │
                       │   Module     │
                       └─────────────┘
```

---

## 🔌 Circuit Diagram

```
                    +12V ──────────────────────────────────┐
                                                           │
                    Arduino UNO R4 WiFi                    │
                   ┌──────────────────┐            ┌──────┴──────┐
     DS18B20 ──►  │ D2  (OneWire)    │            │  [ PELTIER ]│
    (+ 4.7kΩ      │                  │            │  TEC1-12706 │
    pull-up to 5V)│ D9  (PWM) ──────►│──┐         └──────┬──────┘
                  │                  │  │                 │
                  │ SDA ─────────────│  │  ┌─────────────┤ Drain
                  │ SCL ─────────────│  └─►│ Gate        │
                  └──────────────────┘     │  IRFZ44N    │
                                           │             │ Source
                  I2C LCD 16×2             └─────────────┤
                  ┌──────────┐                           │
                  │SDA / SCL │◄── Arduino SDA/SCL       GND ─── GND (shared)
                  └──────────┘

  Capacitor: 47–100µF electrolytic across Peltier terminals (power smoothing)
  Pull-up: 4.7kΩ resistor from DS18B20 data line to +5V
```

---

## 🧩 Hardware Components

| Component | Part Number | Purpose |
|-----------|-------------|---------|
| Microcontroller | Arduino UNO R4 WiFi | WiFi AP, PWM generation, system controller |
| Temperature Sensor | DS18B20 | Accurate 1-Wire digital temperature sensing |
| MOSFET | IRFZ44N / IRLZ44N | High-current switching for Peltier load |
| Peltier Module | TEC1-12706 | Thermoelectric cooling / heating element |
| LCD Display | 16×2 I2C LCD | Local real-time temperature & voltage display |
| Pull-up Resistor | 4.7 kΩ | Required on DS18B20 data line |
| Capacitor | 47–100 µF electrolytic | Power smoothing across Peltier terminals |
| Power Supply | 12V / 5A adapter or battery | Powers the Peltier module |

---

## 🔥 Key Features

### 📶 WiFi Access Point Mode
The UNO R4 creates its own hotspot — **no router required**.  
Connect directly from any phone or laptop.

```
SSID    : Peltier_Control_AP
Password: 12345678
URL     : http://192.168.4.1
```

### 📱 Mobile Web Control Interface
Adjust Peltier voltage from your phone using a **0–12V slider**.  
The MOSFET immediately applies the new PWM duty cycle → instant cooling level change.

### ❄️ Dynamic Cooling via PWM
PWM on pin D9 controls effective voltage across the Peltier:

| Duty Cycle | Effective Voltage | Cooling Level |
|-----------|-------------------|---------------|
| 25% | ~3V | Low |
| 50% | ~6V | Medium |
75% | ~9V | High |
| 100% | 12V | Maximum |

```cpp
// Core PWM logic
int pwmValue = (desiredVoltage / 12.0) * 255;
analogWrite(9, pwmValue);
```

### 🌡️ Real-Time Temperature Monitoring
DS18B20 sensor → readings displayed simultaneously on **LCD** and **web browser**.

### ⚡ Minimal Hardware Design
No buck converters needed — MOSFET + PWM handles all power levels smoothly and efficiently.

---

## 📁 Repository Contents

```
uno-r4-wifi-peltier-controller/
│
├── PELTIER1.ino                  # Arduino code — standalone (no WiFi)
├── peltier-wifi-control-code.ino # Arduino code — with WiFi web interface
├── circuit_image (4).png         # Circuit diagram image
├── LICENSE                       # MIT License
└── README.md
```

> **Two firmware versions included:**
> - `PELTIER1.ino` — Basic version: temperature control + LCD, no WiFi
> - `peltier-wifi-control-code.ino` — Full version: WiFi AP + web UI + LCD + PWM control

---

## 🚀 How to Use

**1️⃣ Wire the hardware** as per the circuit diagram above.

**2️⃣ Flash the firmware**
- For standalone use → upload `PELTIER1.ino`
- For WiFi control → upload `peltier-wifi-control-code.ino`

**3️⃣ Power the system**
- Arduino via USB or VIN pin
- Peltier via separate 12V / 5A supply (shared GND with Arduino)

**4️⃣ Connect to WiFi** (WiFi version only)
```
SSID: Peltier_Control_AP
Pass: 12345678
```

**5️⃣ Open browser** → go to `http://192.168.4.1`

**6️⃣ Adjust the voltage slider** → MOSFET applies PWM → cooling changes instantly.

---

## 📦 Required Libraries

Install via Arduino IDE → Library Manager:

```
OneWire
DallasTemperature
LiquidCrystal_I2C
WiFiS3   (built-in for UNO R4 WiFi)
```

---

## 🌟 Future Improvements

- [ ] PID closed-loop temperature controller (set target temp, auto-regulate)
- [ ] Data logging via SD card or cloud (temperature history graphs)
- [ ] Dual Peltier control (independent channels)
- [ ] Battery-powered portable version with efficiency optimisation
- [ ] OLED display upgrade for richer UI

---

## 👤 Author

**Elamaran Y** — B.Tech Electronics & Communication Engineering, VIT Vellore  
[linkedin.com/in/elamaran-y](https://linkedin.com/in/elamaran-y) · [github.com/Elamaran-hub](https://github.com/Elamaran-hub)

---

*MIT License © 2025 Elamaran-hub*

🚀 UNO R4 WiFi – Peltier Temperature Control System
A WiFi-controlled thermal management system using Arduino UNO R4 WiFi, PWM, MOSFET switching, and DS18B20 sensing.

📌 Overview

This project demonstrates a complete thermal-control system built around the Arduino UNO R4 WiFi.
It controls a 12V Peltier module using MOSFET-based PWM, measures temperature using a DS18B20 sensor,
and provides real-time monitoring through:

a 16×2 I2C LCD, and

a WiFi Access Point web interface that works on any smartphone.

It is designed for wearable cooling, portable devices, and thermal automation.

🧠 System Architecture
Phone (Web UI)
       │ WiFi (AP Mode)
       ▼
Arduino UNO R4 WiFi
       │
       ├── DS18B20 Temp Sensor
       ├── I2C LCD (16x2)
       └── PWM Output (D9)
             │
          MOSFET
             │
       12V Peltier Module

🖥️ Web UI Demo (Animation)
<img src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExNmg5OXJzeGx2NjNqbHZ5eGp2NXM3MzZqaG5rNnR6d2ptNGg2N2hrZiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9bw/MuS4GKmKuhFcg/giphy.gif" width="350">

(Illustrative animation of a slider UI — not exact project UI)

🧩 Circuit Diagram
<img src="./circuit_image.png" width="700">
🔧 Hardware Components
Component	Purpose
🔵 Arduino UNO R4 WiFi	WiFi AP, PWM generator, system controller
🔵 DS18B20 Digital Temperature Sensor	Accurate temperature reading
🔵 N-Channel MOSFET (IRFZ44N/IRLZ44N)	Controls high-current Peltier load
🔵 TEC1-12706 Peltier Module	Cooling / heating element
🔵 16×2 I2C LCD	Displays temperature & voltage
🔵 4.7 kΩ Pull-up Resistor	Required for DS18B20 data line
🔵 47–100 µF Electrolytic Capacitor	Power smoothing for Peltier
🔵 12V Battery / Adapter	Power source for Peltier
🎯 Key Features
🔥 WiFi Access Point Mode

The UNO R4 creates its own WiFi hotspot — no router required.

📱 Mobile Control Interface

Adjust Peltier voltage from your phone using a slider (0–12V effective PWM).

❄️ Dynamic Cooling Control

PWM controls effective voltage using the MOSFET.
Higher duty cycle → more cooling.

🌡️ Real-Time Temperature Monitoring

DS18B20 sensor + LCD + browser display.

🔌 Minimal Hardware

No buck converters — the MOSFET and PWM handle all power levels smoothly.

🧠 How PWM Controls the Peltier (Diagram)
12V Supply  ────────────────┐
                            ▼
                     [ PELTIER ]
                            ▼
PWM (0–255) → MOSFET → Ground

Effective Voltage ≈ DutyCycle × 12V


Example:

25% duty → ~3V

50% duty → ~6V

100% duty → 12V

🧪 Real-World Applications

🔵 Wearable cooling jackets

🔵 Portable cooling pads

🔵 Mini refrigeration prototypes

🔵 Temperature-stabilized electronics compartments

🔵 Medical cold therapy devices

📱 How to Use
1️⃣ Power the system

The Peltier requires 12V.
Arduino can be powered via USB or 12V input.

2️⃣ Connect to WiFi

Your phone connects to:

SSID	Password
Peltier_Control_AP	12345678
3️⃣ Open browser

Go to:

http://192.168.4.1

4️⃣ Adjust the voltage slider

The MOSFET immediately applies the new PWM → new cooling level.

🧾 Project Files
uno-r4-wifi-peltier-controller/
│── circuit_image.png
│── peltier_controller.ino
│── README.md

💻 Code Snippet (Full code inside repo)
int pwmValue = (desiredVoltage / 12.0) * 255;
analogWrite(9, pwmValue);

⭐ Future Improvements

🔵 Add PID temperature control

🔵 Data logging via SD card or cloud

🔵 Dual Peltier control

🔵 Battery efficiency optimization

🙌 Acknowledgments

Thanks to the Arduino UNO R4 WiFi platform and DS18B20 library contributors.

📬 Contact

Feel free to open issues, fork this repo, or suggest improvements.

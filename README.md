<<<<<<< HEAD
# Bluetooth Hydroponics Pump Controller

An Arduino Uno firmware that controls a water pump via Bluetooth (HC-05).  
Supports manual ON/OFF commands and a non-blocking automatic timed cycle.

---

## Project Overview

This firmware turns an Arduino Uno into a Bluetooth-controlled irrigation
controller for a small hydroponic system. Commands are sent from any phone
Bluetooth terminal app (e.g. **Serial Bluetooth Terminal** on Android).

**Auto mode** runs the pump in a continuous cycle:
- **ON** for 10 seconds
- **OFF** for 30 seconds
- Repeats indefinitely until a manual command overrides it

All timing uses `millis()` — no `delay()` calls — so the Arduino stays
responsive to new Bluetooth commands at all times.

---

## Components

| Component              | Quantity | Notes                                      |
|------------------------|----------|--------------------------------------------|
| Arduino Uno            | 1        | Any 5 V Uno clone works                    |
| HC-05 Bluetooth Module | 1        | Pre-paired at 9600 baud                    |
| 5 V Relay Module       | 1        | Optocoupler-isolated recommended            |
| DC Water Pump          | 1        | 3–12 V submersible pump                    |
| External power supply  | 1        | Match pump voltage; **never power from Arduino** |
| Jumper wires           | —        | Male-to-male and male-to-female            |
| Breadboard (optional)  | 1        | For prototyping                            |

---

## Wiring

See **`wiring_diagram.txt`** for a full text description.

Quick summary:

```
HC-05  VCC  → Arduino 5V
HC-05  GND  → Arduino GND
HC-05  TX   → Arduino D2  (SoftwareSerial RX)
HC-05  RX   → Arduino D3  (via 1kΩ/2kΩ voltage divider — HC-05 RX is 3.3 V!)

Relay  VCC  → Arduino 5V
Relay  GND  → Arduino GND
Relay  IN   → Arduino D8

Pump         → Relay NO (Normally Open) + external power supply
```

---

## How to Upload

1. Install the **Arduino IDE** (version 1.8+ or 2.x).
2. Open `bluetooth-hydroponics-pump.ino`.
3. Select **Board → Arduino Uno** and the correct **COM port**.
4. Click **Upload**.
5. Open **Serial Monitor** at **9600 baud** to see debug output.

> ⚠️ Disconnect the HC-05 TX/RX wires from D2/D3 before uploading.  
> SoftwareSerial conflicts with the USB upload process.

---

## Bluetooth Commands

See **`commands.txt`** for a full command reference.

| Command  | Effect                                      |
|----------|---------------------------------------------|
| `ON`     | Turn pump ON (manual mode)                  |
| `OFF`    | Turn pump OFF (manual mode)                 |
| `AUTO`   | Enable timed cycle (10 s on / 30 s off)     |
| `STATUS` | Print current mode and pump state           |

Commands are **case-insensitive** — `on`, `ON`, `On` all work.

---

## File Structure

```
bluetooth-hydroponics-pump/
├── bluetooth-hydroponics-pump.ino   ← main firmware
├── README.md                        ← this file
├── wiring_diagram.txt               ← full wiring reference
└── commands.txt                     ← Bluetooth command reference
```

---

## Author

Jeremy A. — Mechanical Engineering Student  
Hydroponic Automation Project · 2026
=======
# 🌱 Hydroponic Control System

A smart, modular hydroponic system powered by Arduino, designed for automated watering, remote control, and scalable agri-tech experimentation.

---

## 🚀 Overview

This project is a real-world embedded system that combines:

* Robotics (pan & tilt servo system)
* IoT communication (Bluetooth via HC-05)
* Power electronics (battery + LM2596 regulation)
* Automation (pump control & timed irrigation)

Built as an MVP for a scalable, AI-assisted hydroponic farm.

---

## ⚙️ Features

* 📡 **Bluetooth Control (HC-05)**

  * Send commands from phone/laptop
* 🎯 **Pan & Tilt Mechanism**

  * Dual servo system for directional control
* 💧 **Automated Pump System**

  * Relay-controlled water flow
* 🔋 **Battery Powered**

  * 18650 pack + BMS + LM2596 5V regulation
* 🧠 **Expandable Architecture**

  * Ready for sensors, AI logic, and IoT upgrades

---

## 🧩 Hardware Components

* Arduino Uno/Nano
* HC-05 Bluetooth Module
* 2x Servo Motors (Pan & Tilt)
* Water Pump (5V or 12V)
* LM2596 Buck Converter
* Lithium Battery Pack (2S/3S with BMS)
* Relay Module or MOSFET Driver
* Water Level Sensor (optional)

---

## 🔌 System Architecture

Battery → BMS → LM2596 → 5V Rail
→ Arduino + Servos + HC-05

All grounds are shared (common ground system).

---

## 📲 Bluetooth Commands

| Command      | Function               |
| ------------ | ---------------------- |
| `PUMP ON`    | Turns pump on          |
| `PUMP OFF`   | Turns pump off         |
| `PAN 0-180`  | Move pan servo         |
| `TILT 0-180` | Move tilt servo        |
| `HOME`       | Reset servos to center |
| `SCAN`       | Sweep motion           |

---

## 🧠 Code Structure

* Modular command parsing
* Non-blocking servo control (expandable)
* Ready for sensor integration

---

## 🛠️ Future Improvements

* Water level automation (auto pump stop)
* Mobile app UI
* AI-based irrigation optimization
* Solar + agrovoltaic integration
* Remote monitoring dashboard

---

## 📸 Demo (Coming Soon)

Project build and testing videos will be added.

---

## 👤 Author

Jeremy Ahamioje
Aspiring polymath building scalable agri-tech systems.

---

## ⚠️ Disclaimer

This is a prototype system. Ensure proper battery handling and electrical safety when scaling.
This is a prototype, some features may be absent
>>>>>>> 8bcfef51102e82ad3963666b0c2b436408670f87

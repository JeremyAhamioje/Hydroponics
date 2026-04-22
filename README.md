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

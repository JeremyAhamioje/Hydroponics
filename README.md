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

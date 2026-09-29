# Hydroponic Control System

Arduino firmware for a Bluetooth-controlled hydroponic irrigation rig — manual pump control plus a non-blocking automatic watering cycle, built as the first stage of a modular agri-tech system.

Write-up in the blog section of [portfolio-pa3u.vercel.app](https://portfolio-pa3u.vercel.app/)

---

## What is built

An Arduino Uno drives a submersible pump through an optocoupler-isolated relay, taking commands over an HC-05 Bluetooth module from any phone terminal app.

**Auto mode** cycles the pump 10 seconds on, 30 seconds off, indefinitely, until a manual command overrides it.

All timing uses `millis()` rather than `delay()`, so the board stays responsive to incoming Bluetooth commands throughout the cycle. A `delay()`-based loop would be deaf to an OFF command for up to 30 seconds — which, with a pump running, is the one moment responsiveness actually matters.

### Commands

| Command | Effect |
|---|---|
| `ON` | Pump on, manual mode |
| `OFF` | Pump off, manual mode |
| `AUTO` | Timed cycle — 10 s on / 30 s off |
| `MANUAL` | Leave auto mode, hold current state |
| `STATUS` | Report current mode and pump state |

Case-insensitive — `on`, `ON` and `On` all parse.

## Hardware

| Component | Qty | Notes |
|---|---|---|
| Arduino Uno | 1 | Any 5 V clone |
| HC-05 Bluetooth module | 1 | Pre-paired, 9600 baud |
| 5 V relay module | 1 | Optocoupler-isolated recommended |
| DC water pump | 1 | 3–12 V submersible |
| External supply | 1 | Match pump voltage — **never drive the pump from the Arduino** |
| Jumper wires, breadboard | — | For prototyping |

## Wiring

Full reference in [`wiring_diagram.txt`](./wiring_diagram.txt).

```
HC-05  VCC → 5V        Relay VCC → 5V
HC-05  GND → GND       Relay GND → GND
HC-05  TX  → D2        Relay IN  → D8
HC-05  RX  → D3        Pump      → Relay NO + external supply
```

**D3 to HC-05 RX must go through a 1 kΩ / 2 kΩ divider.** The HC-05's RX pin is 3.3 V and the Arduino drives 5 V; wired directly it works for a while and then stops working permanently.

## Uploading

1. Open `bluetooth-hydroponics-pump.ino` in the Arduino IDE (1.8+ or 2.x)
2. Board → Arduino Uno, select the COM port
3. Upload, then open Serial Monitor at 9600 baud for debug output

**Disconnect HC-05 TX/RX from D2/D3 first** — SoftwareSerial conflicts with the USB upload.

## Files

```
bluetooth-hydroponics-pump.ino   firmware
wiring_diagram.txt               full wiring reference
commands.txt                     command reference
```

---

## Where this is going

The pump loop is stage one of a larger system design: a battery-powered, remotely controlled grow rig.

- **Power** — 2S/3S 18650 pack → BMS → LM2596 buck converter → shared 5 V rail, common ground throughout
- **Pan & tilt** — dual-servo directional mount, with non-blocking servo control alongside the existing pump cycle
- **Water-level sensing**, so auto mode stops on an empty reservoir instead of running the pump dry
- Mobile app UI, remote monitoring, and irrigation timing driven by sensor history rather than a fixed cycle
- Solar / agrovoltaic supply

Those are planned, not built — the firmware in this repo is the pump controller.

---

**Safety.** This is a prototype. Lithium packs and mains-adjacent pump supplies both deserve care; check polarity and current ratings before scaling anything here.

Jeremy Ahamioje — Mechanical Engineering · Hydroponic Automation Project, 2026

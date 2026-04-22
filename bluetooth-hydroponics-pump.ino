// ============================================================
//  bluetooth-hydroponics-pump.ino
//  Bluetooth-controlled water pump for a hydroponic system.
//
//  Features:
//    · Manual ON / OFF via Bluetooth commands
//    · AUTO mode — non-blocking timed pump cycles
//    · HC-05 on SoftwareSerial (D2 RX, D3 TX)
//    · Pump relay / transistor on D8
//    · USB Serial debug output at 9600 baud
//
//  Author : Jeremy A.
//  Board  : Arduino Uno
// ============================================================

#include <SoftwareSerial.h>

// ─── PIN DEFINITIONS ─────────────────────────────────────────
const int BT_RX_PIN  = 2;   // Arduino RX  ← HC-05 TX
const int BT_TX_PIN  = 3;   // Arduino TX  → HC-05 RX
const int PUMP_PIN   = 8;   // Relay / transistor base

// ─── TIMING CONSTANTS (milliseconds) ─────────────────────────
const unsigned long PUMP_ON_DURATION  = 10000UL;  // 10 s on
const unsigned long PUMP_OFF_DURATION = 30000UL;  // 30 s off

// ─── OPERATING MODES ─────────────────────────────────────────
enum Mode { MANUAL, AUTO_MODE };

// ─── STATE VARIABLES ─────────────────────────────────────────
Mode         currentMode    = MANUAL;
bool         pumpIsOn       = false;
unsigned long lastSwitchTime = 0;   // millis() of last pump state change

// ─── SOFTWARESERIAL INSTANCE ─────────────────────────────────
SoftwareSerial BT(BT_RX_PIN, BT_TX_PIN);

// ============================================================
//  HELPERS
// ============================================================

void setPump(bool on) {
  pumpIsOn = on;
  digitalWrite(PUMP_PIN, on ? HIGH : LOW);
  Serial.println(on ? "[PUMP] ON" : "[PUMP] OFF");
}

void handleCommand(String cmd) {
  cmd.trim();

  // ── Force uppercase for case-insensitive matching ──────────
  String upper = cmd;
  for (int i = 0; i < upper.length(); i++) {
    upper[i] = toupper(upper[i]);
  }

  Serial.print("[CMD] Received: ");
  Serial.println(upper);

  if (upper == "ON") {
    currentMode = MANUAL;
    setPump(true);
    BT.println("OK: Pump ON (manual)");

  } else if (upper == "OFF") {
    currentMode = MANUAL;
    setPump(false);
    BT.println("OK: Pump OFF (manual)");

  } else if (upper == "AUTO") {
    currentMode    = AUTO_MODE;
    lastSwitchTime = millis();
    setPump(true);   // start the first ON phase immediately
    BT.println("OK: AUTO mode started (10s ON / 30s OFF)");
    Serial.println("[MODE] AUTO enabled");

  } else if (upper == "STATUS") {
    // Handy diagnostic command
    BT.print("Mode: ");
    BT.println(currentMode == AUTO_MODE ? "AUTO" : "MANUAL");
    BT.print("Pump: ");
    BT.println(pumpIsOn ? "ON" : "OFF");

  } else {
    BT.println("ERR: Unknown command. Use ON / OFF / AUTO / STATUS");
    Serial.print("[CMD] Unknown: ");
    Serial.println(upper);
  }
}

// ============================================================
//  AUTO MODE LOOP (non-blocking)
// ============================================================

void runAutoMode() {
  unsigned long now     = millis();
  unsigned long elapsed = now - lastSwitchTime;

  if (pumpIsOn && elapsed >= PUMP_ON_DURATION) {
    // ON phase complete → switch OFF
    setPump(false);
    lastSwitchTime = now;
    Serial.print("[AUTO] OFF phase. Next ON in ");
    Serial.print(PUMP_OFF_DURATION / 1000);
    Serial.println("s");

  } else if (!pumpIsOn && elapsed >= PUMP_OFF_DURATION) {
    // OFF phase complete → switch ON
    setPump(true);
    lastSwitchTime = now;
    Serial.print("[AUTO] ON phase. Next OFF in ");
    Serial.print(PUMP_ON_DURATION / 1000);
    Serial.println("s");
  }
}

// ============================================================
//  SETUP
// ============================================================

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);   // safe default — pump OFF on boot

  Serial.println("==============================================");
  Serial.println("  Bluetooth Hydroponics Pump Controller");
  Serial.println("  Commands: ON | OFF | AUTO | STATUS");
  Serial.println("==============================================");
}

// ============================================================
//  MAIN LOOP
// ============================================================

void loop() {
  // ── 1. Read Bluetooth input ───────────────────────────────
  if (BT.available()) {
    String incoming = BT.readStringUntil('\n');
    handleCommand(incoming);
  }

  // ── 2. Run auto-cycle logic if in AUTO mode ───────────────
  if (currentMode == AUTO_MODE) {
    runAutoMode();
  }
}

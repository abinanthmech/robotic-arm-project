# 6-DOF Robot Arm — ESP32 WebSocket Controller

A firmware for controlling a 6 degree-of-freedom robotic arm using an **ESP32**, with a browser-based control panel, smooth servo motion, and a **record/playback ("Teach mode")** system — all served over a self-hosted WiFi access point, no external network or app required.

---

## Features

- 📶 **Standalone WiFi Access Point** — no router needed, connect straight to the ESP32
- 🎛️ **Web-based control panel** — slider control for each joint, served directly from the ESP32
- ⚡ **Real-time control via WebSocket** — low-latency compared to standard HTTP requests
- 🤖 **Smooth motion ramping** — joints ease toward target position instead of snapping
- 🎚️ **Adjustable speed** — increase/decrease motion speed on the fly
- 🔴 **Record mode** — capture a sequence of manual joint movements with timing
- ▶️ **Playback mode** — replay a recorded sequence automatically
- 🏠 **One-tap Home position** — return all joints to a safe default pose

---

## Used Hardware & Software

### Hardware

- **Microcontroller:** ESP32
- **Servo Motors:** 6 × Servo Motors
- **Robot Arm:** 6-DOF Robotic Arm
- **Servo Connections:**
  - Base → GPIO 27
  - Shoulder → GPIO 26
  - Elbow → GPIO 25
  - Wrist Pitch → GPIO 14
  - Wrist Roll → GPIO 12
  - Gripper → GPIO 33
  - External 5V power supply for servos recommended (do **not** power 6 servos off the ESP32's onboard 3.3V/5V regulator)
  - Default home position (degrees): `{151, 45, 128, 1, 58, 102}` — adjust `homePos[]` in the code to match your arm's safe resting pose

### Software

- **Development Environment:** Arduino IDE
- **Programming Language:** C++
- **Framework:** Arduino Framework for ESP32
- **Web Interface:** HTML + JavaScript
- **Communication:** WebSocket


---

## Libraries Used

- [`ESPAsyncWebServer`](https://github.com/me-no-dev/ESPAsyncWebServer)
- [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP)
- [`ESP32Servo`](https://github.com/madhephaestus/ESP32Servo)

Install these via the Arduino Library Manager or PlatformIO before building.

---

## How It Works

### 1. Connectivity
On boot, the ESP32 creates its own WiFi network:

- **SSID:** `RobotArm`
- **Password:** `12345678`

> ⚠️ Change this password in the source before using the arm anywhere with other WiFi devices nearby, since the default is easy to guess.

Connect to the network, then open `http://192.168.4.1/` in a browser to load the control panel.

### 2. Control Panel → WebSocket
The web page opens a WebSocket connection to `/RobotArmInput`. Every UI action sends a simple `"KEY,VALUE"` string message, e.g.:

```
Elbow,90
HOME,1
REC,1
PLAY,1
SPD+,1
```

The firmware parses the key/value pair and reacts accordingly — no JSON parsing overhead, keeping things fast and lightweight on the microcontroller.

### 3. Smooth Motion
Rather than jumping directly to a commanded angle, each servo's `currentPos` steps 1° at a time toward `targetPos` on a timer (`speedDelay`, default 25 ms). This produces smooth, natural-looking movement and prevents mechanical shock or current spikes. `SPD+` / `SPD-` adjust this delay live (5–100 ms range).

### 4. Record & Playback ("Teach Mode")
This firmware includes a lightweight teach-pendant workflow:

1. Press **RECORD ON** and manually move the joints using the sliders.
2. Every move is logged as a `{ servo index, target value, time since last move }` step.
3. Press **RECORD OFF** to stop capturing.
4. Press **PLAY ON** to replay the exact sequence of moves, with the original timing between steps.

This lets you "teach" the arm a motion by hand and have it repeat that motion automatically.

> **Note:** Home commands issued during recording are not captured in the step sequence — only direct servo movements are logged.







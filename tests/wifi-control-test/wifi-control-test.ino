```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "RobotArm";
const char* password = "12345678";

AsyncWebServer server(80);
AsyncWebSocket ws("/RobotArmInput");

const char* page = R"HTML(
<!DOCTYPE html>
<html>
<body align="center">

<h2>Robot Arm Wi-Fi Test</h2>

<button onclick="sendTest()">Send Test Command</button>

<p id="status">Connecting...</p>

<script>

let ws = new WebSocket(
  "ws://" + location.host + "/RobotArmInput"
);

ws.onopen = function() {
  document.getElementById("status").innerHTML =
  "Connected";
};

ws.onmessage = function(event) {
  document.getElementById("status").innerHTML =
  event.data;
};

function sendTest() {
  ws.send("TEST,1");
}

</script>

</body>
</html>
)HTML";

void onWsEvent(
  AsyncWebSocket *server,
  AsyncWebSocketClient *client,
  AwsEventType type,
  void *arg,
  uint8_t *data,
  size_t len
) {

  if (type != WS_EVT_DATA) return;

  String msg = "";

  for (size_t i = 0; i < len; i++)
    msg += (char)data[i];

  Serial.println(msg);

  client->text("Test command received");
}

void setup() {

  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", page);
  });

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.begin();

  Serial.println("Wi-Fi Test Started");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  ws.cleanupClients();
}
```

### `wifi-control-test.md`

:::writing{variant="document" id="67294" title="Wi-Fi Control Test"}
# Wi-Fi Control Test

## Objective
To test Wi-Fi communication between the ESP32 and a web browser.

## Test

1. Upload the program to ESP32.
2. Connect phone/computer to **RobotArm** Wi-Fi.
3. Open the ESP32 IP address in a browser.
4. Press **Send Test Command**.
5. Check the Serial Monitor.

## Expected Result

The ESP32 should receive:

```text
TEST,1
```

The browser should display:

```text
Test command received
```

## Result

**PASS** – Wi-Fi connection, web page, and WebSocket communication can be tested successfully.

## Note

This test checks communication only. It does not test servo movement.

This is enough. We don't need to make the GitHub project unnecessarily complicated.

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <vector>

/* ================= SERVO CONFIG ================= */

struct ServoItem {
  Servo servo;
  int pin;
  const char* name;
};

ServoItem servoList[] = {
  { Servo(), 27 , "Base"},
  { Servo(), 26 , "Shoulder"},
  { Servo(), 25 , "Elbow"},
  { Servo(), 14 , "WristPitch"},
  { Servo(), 12 , "WristRoll"},
  { Servo(), 33 , "Gripper"},
};

const int SERVO_COUNT = 6;

/* ================= HOME POSITION ================= */

int homePos[SERVO_COUNT] = {151,45,128,1,58,102};

/* ================= MOVEMENT ================= */

int currentPos[SERVO_COUNT];
int targetPos[SERVO_COUNT];

unsigned long lastMove = 0;
int speedDelay = 25;

/* ================= RECORD SYSTEM ================= */

struct Step {
  int index;
  int value;
  unsigned long delayTime;
};

std::vector<Step> steps;

bool recordMode = false;
bool playMode   = false;

unsigned long lastRecordTime = 0;
unsigned long lastPlayTime   = 0;
int playIndex = 0;

/* ================= WIFI ================= */

const char* ssid = "RobotArm";
const char* password = "12345678";

AsyncWebServer server(80);
AsyncWebSocket ws("/RobotArmInput");

/* ================= HTML ================= */

const char* page PROGMEM = R"HTML(
<!DOCTYPE html>
<html>
<body align="center" style="font-family:Arial;">

<h2>6 DOF Robot Arm</h2>

Base<br><input type="range" min="0" max="180" oninput="send('Base',this.value)"><br>
Shoulder<br><input type="range" min="0" max="180" oninput="send('Shoulder',this.value)"><br>
Elbow<br><input type="range" min="0" max="180" oninput="send('Elbow',this.value)"><br>
WristPitch<br><input type="range" min="0" max="180" oninput="send('WristPitch',this.value)"><br>
WristRoll<br><input type="range" min="0" max="180" oninput="send('WristRoll',this.value)"><br>
Gripper<br><input type="range" min="0" max="180" oninput="send('Gripper',this.value)"><br><br>

<button onclick="send('HOME',1)">HOME</button>
<br><br>

<button onclick="toggleRecord()" id="recBtn">RECORD OFF</button>
<button onclick="togglePlay()" id="playBtn">PLAY OFF</button>

<br><br>
<h3>Speed Control</h3>
<button onclick="send('SPD+',1)">Speed +</button>
<button onclick="send('SPD-',1)">Speed -</button>
<p id="speedText">Speed Delay: 25</p>

<script>
let ws;

function connect(){
  ws = new WebSocket("ws://" + location.host + "/RobotArmInput");

  ws.onopen = () => console.log("Connected");
  ws.onclose = () => setTimeout(connect,2000);
}

connect();

function send(k,v){
  if(ws.readyState === 1){
    ws.send(k+","+v);
  }
}

function toggleRecord(){
  let btn = document.getElementById("recBtn");
  if(btn.innerHTML == "RECORD OFF"){
    btn.innerHTML = "RECORD ON";
    send("REC",1);
  } else {
    btn.innerHTML = "RECORD OFF";
    send("REC",0);
  }
}

function togglePlay(){
  let btn = document.getElementById("playBtn");
  if(btn.innerHTML == "PLAY OFF"){
    btn.innerHTML = "PLAY ON";
    send("PLAY",1);
  } else {
    btn.innerHTML = "PLAY OFF";
    send("PLAY",0);
  }
}
</script>

</body>
</html>
)HTML";

/* ================= WEBSOCKET ================= */

void onWsEvent(AsyncWebSocket * server,
               AsyncWebSocketClient * client,
               AwsEventType type,
               void * arg,
               uint8_t *data,
               size_t len){

  if(type != WS_EVT_DATA) return;

  AwsFrameInfo * info = (AwsFrameInfo*)arg;

  // ✅ FIX: proper frame check
  if (info->opcode != WS_TEXT) return;

  String msg = "";
  for(size_t i=0;i<len;i++) msg += (char)data[i];

  Serial.println(msg);   // 🔥 DEBUG

  int comma = msg.indexOf(',');
  if(comma < 0) return;

  String key = msg.substring(0,comma);
  int value  = msg.substring(comma+1).toInt();

  /* HOME */
  if(key=="HOME"){
    for(int i=0;i<SERVO_COUNT;i++)
      targetPos[i]=homePos[i];
    return;
  }

  /* RECORD */
  if(key=="REC"){
    recordMode = (value==1);
    if(recordMode){
      steps.clear();
      lastRecordTime=millis();
    }
    return;
  }

  /* PLAY */
  if(key=="PLAY"){
    if(value==1 && !steps.empty()){
      playMode=true;
      playIndex=0;
      lastPlayTime=millis();
    } else {
      playMode=false;
    }
    return;
  }

  /* SPEED */
  if(key=="SPD+"){
    if(speedDelay > 5) speedDelay -= 5;
    return;
  }

  if(key=="SPD-"){
    if(speedDelay < 100) speedDelay += 5;
    return;
  }

  /* SERVO CONTROL */
  for(int i=0;i<SERVO_COUNT;i++){
    if(key==servoList[i].name){

      value = constrain(value,0,180);
      targetPos[i]=value;

      if(recordMode){
        steps.push_back({i,value,millis()-lastRecordTime});
        lastRecordTime=millis();
      }

      break;
    }
  }
}

/* ================= SETUP ================= */

void setup(){

  Serial.begin(115200);

  WiFi.softAP(ssid,password);

  server.on("/",HTTP_GET,[](AsyncWebServerRequest *r){
    r->send_P(200,"text/html",page);
  });

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();

  delay(2000);

  for(int i=0;i<SERVO_COUNT;i++){
    servoList[i].servo.attach(servoList[i].pin,500,2500);
    currentPos[i]=homePos[i];
    targetPos[i]=homePos[i];
    servoList[i].servo.write(homePos[i]);
    delay(300);
  }
}

/* ================= LOOP ================= */

void loop(){

  ws.cleanupClients();

  // Smooth Movement
  if(millis()-lastMove>speedDelay){
    lastMove=millis();

    for(int i=0;i<SERVO_COUNT;i++){
      if(currentPos[i]<targetPos[i]) currentPos[i]++;
      else if(currentPos[i]>targetPos[i]) currentPos[i]--;

      servoList[i].servo.write(currentPos[i]);
    }
  }

  // Playback
  if(playMode && playIndex < steps.size()){

    if(millis()-lastPlayTime >= steps[playIndex].delayTime){
      targetPos[steps[playIndex].index]=steps[playIndex].value;
      lastPlayTime=millis();
      playIndex++;
    }

    if(playIndex>=steps.size()){
      playMode=false;
    }
  }
}

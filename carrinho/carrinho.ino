#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WebSocketsServer.h>


//motor
// Motor A
const int motor1Pin1 = 2;
const int motor1Pin2 = 14;
const int enable1Pin = 12;

// Motor B
const int motor2Pin1 = 15;
const int motor2Pin2 = 13;
const int enable2Pin = 0;

// configurando pwm
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int velocidade = 255;
//motor

WebSocketsServer webSocket(81); // Porta WebSocket

void handleWebSocketMessage(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_TEXT) {
    Serial.printf("[%u] Text received: %s\n", num, payload);
    frente();
  } else if (type == WStype_CONNECTED) {
    Serial.printf("[%u] WebSocket Connected\n", num);
  }
}


const char* ssid = "SATC IOT";
const char* password = "IOT2023@";

int btnGPIO = 0;
int btnState = false;

AsyncWebServer server(80);

void setup() {
  //motor
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);  
  ledcAttachPin(enable2Pin, pwmChannel);

  ledcWrite(pwmChannel, velocidade);
  //motor
  Serial.begin(115200);
  delay(10);

  pinMode(btnGPIO, INPUT);

  Serial.println();
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int tryDelay = 500;
  int numberOfTries = 20;

  while (true) {
    switch (WiFi.status()) {
      case WL_NO_SSID_AVAIL:
        Serial.println("[WiFi] SSID not found");
        break;
      case WL_CONNECT_FAILED:
        Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
        return;
      case WL_CONNECTION_LOST:
        Serial.println("[WiFi] Connection was lost");
        break;
      case WL_SCAN_COMPLETED:
        Serial.println("[WiFi] Scan is completed");
        break;
      case WL_DISCONNECTED:
        Serial.println("[WiFi] WiFi is disconnected");
        break;
      case WL_CONNECTED:
        Serial.println("[WiFi] WiFi is connected!");
        Serial.print("[WiFi] IP address: ");
        Serial.println(WiFi.localIP());
        setupServer();
        return;
      default:
        Serial.print("[WiFi] WiFi Status: ");
        Serial.println(WiFi.status());
        break;
    }
    delay(tryDelay);

    if (numberOfTries <= 0) {
      Serial.print("[WiFi] Failed to connect to WiFi!");
      WiFi.disconnect();
      return;
    } else {
      numberOfTries--;
    }
  }
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  webSocket.begin();
  webSocket.onEvent(handleWebSocketMessage);
}

void setupServer() {
  if (!SPIFFS.begin(true)) {
    Serial.println("Falha ao montar o sistema de arquivos SPIFFS.");
    return;
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/script.js", "application/javascript");
  });
  server.begin();
  
  webSocket.begin();
  webSocket.onEvent(handleWebSocketMessage);
}

void loop() {
  webSocket.loop();
  btnState = digitalRead(btnGPIO);

  if (btnState == LOW) {
    Serial.println("[WiFi] Disconnecting from WiFi!");
    if (WiFi.disconnect(true, false)) {
      Serial.println("[WiFi] Disconnected from WiFi!");
    }
    delay(1000);
  }
}

void frente(){
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
}

void tras(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
}

void gesq(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
}

void gdir(){
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
}

#include <ESP32Servo.h>
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WebSocketsServer.h>

// configs do motor

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

int btnGPIO = 0;
int btnState = false;

const char *ssid = "Carrinho";
const char *password = "Carrinho";

AsyncWebServer server(80);


WebSocketsServer webSocket(81); // Porta WebSocket
void handleWebSocketMessage(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_TEXT) {   
    if (strcmp((const char*)payload, "frente") == 0) {
      Serial.println("frente!");
      frente();
    }
    else if (strcmp((const char*)payload, "gesq") == 0){
      Serial.println("gesq!");
      gesq();
    }
    else if (strcmp((const char*)payload, "gdir") == 0){
      Serial.println("gdir!");
      gdir();
    }
    else if (strcmp((const char*)payload, "tras") == 0){
      Serial.println("tras!");
      tras();
    }
    else if (strcmp((const char*)payload, "parado") == 0) {
      Serial.println("parado!");
      parado();
    }
}
}

void setup() {
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

  if (!SPIFFS.begin(true)) {
    Serial.println("Falha ao montar o sistema de arquivos SPIFFS.");
    return;
  }

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.begin(115200);
  Serial.print("Endereço IP do AP: ");
  Serial.println(IP);

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

void parado(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
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


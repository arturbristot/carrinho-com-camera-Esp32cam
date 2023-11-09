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
}

void loop() {
  // put your main code here, to run repeatedly:
  frente();
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

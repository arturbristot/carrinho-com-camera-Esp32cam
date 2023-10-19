int m1 = 2;
int m2 = 14;
int m3 = 15;
int m4 = 13;
int spd = (12, 16);
int velo;

void setup() {
  // put your setup code here, to run once:
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(spd, OUTPUT);  
  velo = 20;
}

void loop() {
  frente();
  
}

void frente(){
 analogWrite(spd, velo);
 digitalWrite(m1, 1);
 digitalWrite(m2, 0);
  
 digitalWrite(m3, 1);
 digitalWrite(m4, 0);
}

void tras(){
 analogWrite(spd, velo);
 digitalWrite(m1, 0);
 digitalWrite(m2, 1);
  
 digitalWrite(m3, 0);
 digitalWrite(m4, 1);
}

void gesq(){
 analogWrite(spd, velo);
 digitalWrite(m1, 1);
 digitalWrite(m2, 0);
  
 digitalWrite(m3, 0);
 digitalWrite(m4, 1);
}

void gdir(){
 analogWrite(spd, velo);
 digitalWrite(m1, 0);
 digitalWrite(m2, 1);
  
 digitalWrite(m3, 1);
 digitalWrite(m4, 0);
}

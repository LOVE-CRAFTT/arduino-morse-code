#define BUZZER 9

void setup() {
  pinMode(BUZZER, OUTPUT);
  Serial.begin(115200);
}

void loop() {

 analogWrite(BUZZER, 10);
  
}

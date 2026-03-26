#define LED 13

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void flicker(size_t delay_time) {
  digitalWrite(LED, HIGH);
  delay(delay_time);
  digitalWrite(LED, LOW);
  delay(delay_time);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 1; i < 5000; i *= 2) {
    Serial.println(i);
    flicker(i);
  }  
}

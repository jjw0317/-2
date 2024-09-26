int LED=7,i=0;
void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED,LOW);
  delay(1000);
  for(int i=0;i<5;i++){
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
  digitalWrite(LED,HIGH);
  delay(1000);
  while(1){
  }
}

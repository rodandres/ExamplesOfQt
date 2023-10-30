int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//if(Serial.available()){

  int val = Serial.parseInt();
  if(val == 1){
    digitalWrite(ledPin, HIGH);
  }
  if(val == 2){
    digitalWrite(ledPin, LOW);
  }
//}
}

//modificacion sadasdsadas
//sadasd
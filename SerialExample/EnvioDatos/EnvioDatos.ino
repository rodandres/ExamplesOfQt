void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
/*Serial.print("I,");
for(int i=0; i<10;i++){
  Serial.print(i);
  Serial.print(",");
  delay(200);
}
Serial.print("F,");
Serial.print("A1,B2,C3,A4,B5,C6,A7,B8,C9,");*/

int randomNumber = random(101);
Serial.print("A"+String(randomNumber)+",B"+String(randomNumber+1)+",C"+String(randomNumber+2)+",");

delay(500);
}

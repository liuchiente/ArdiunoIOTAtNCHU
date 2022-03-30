const int ledPin=3;
const int potPin=A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  pinMode(potPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val=analogRead(potPin);
  int val2=val/4;
  analogWrite(ledPin,val2);
  //Serial.write(val2);
  /*for(val=0;val<256;val=val+15){
    analogWrite(ledPin,val);
    delay(150);
    }

   for(val=255;val>=0;val=val-15){
    analogWrite(ledPin,val);
    delay(150);
    }*/
}

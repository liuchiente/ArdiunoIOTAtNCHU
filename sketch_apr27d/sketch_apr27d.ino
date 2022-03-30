const int ledPin=3;
void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);
}
int val=0;
int bk=0;
void loop() {
  // put your main code here, to run repeatedly:
  uint8_t btn = digitalRead(2);
  if (btn == LOW){
    
    if(val>=255){
      bk=1;
      }else if(val<=0){
       bk=0;
      }
      
      if(bk==0){
           val=val+30;
        }else{
                val=val-30;
          }

          if(val>=255) val=255;
          if(val<=0) val=0;
          
      analogWrite(ledPin,val);
      Serial.println(val);
      delay(250);
  }
}

#define LedPin 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT);
  digitalWrite(LedPin,HIGH);
  SetupTimer();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<101;i++){
    Serial.println(i);
    //delay(1000);
  }
}

void SetupTimer(){
  //初始暫存器
 TCCR1A=0;
 TCCR1B=0;
 TCNT1=0;
 
 //CTC模式
 TCCR1B=TCCR1B|(1<<3);

  //除頻和上限
 TCCR1B=TCCR1B|(1<<2);
 OCR1A=31250;
 //TCCR1B=TCCR1B|(1<<WGM12);

 //致能中斷
 TIMSK1=TIMSK1|(1<<1);
}

ISR(TIMER1_COMPA_vect){
  digitalWrite(LedPin,!digitalRead(LedPin));  
}

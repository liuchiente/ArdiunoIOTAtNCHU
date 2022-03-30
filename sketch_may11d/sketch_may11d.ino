#define LedPin 13
#define ButtonPin 2
int flag=1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin,OUTPUT);
  pinMode(ButtonPin,INPUT_PULLUP);
  digitalWrite(LedPin,LOW);
  EIMSK |=_BV(INT0);
  EICRA &=~_BV(ISC01);
  EICRA |=_BV(ISC00);
}

void loop() {
}

void my_ISR(){
  digitalWrite(LedPin,!digitalRead(LedPin));
}

//INTO固定呼叫中斷的程式, 傳入中斷向量
ISR(INT0_vect){
  my_ISR();
}

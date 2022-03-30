#define LedPin 13
#define ButtonPin 2
int flag=1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin,OUTPUT);
  pinMode(ButtonPin,INPUT_PULLUP);
  digitalWrite(LedPin,LOW);
  attachInterrupt(digitalPinToInterrupt(ButtonPin),my_ISR,CHANGE);
}

void loop() {
}

void my_ISR(){
  digitalWrite(LedPin,!digitalRead(LedPin));
}

#include <avr/wdt.h>
#define TIMEOUT WDTO_4S
#define LED_PIN 13
volatile int flag=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);

  MCUSR&=~(1<<WDRF);
  WDTCSR|=(1<<WDCE)|(1<<WDE);
  WDTCSR|=1<<WDP3|1<<WDP0;
  WDTCSR|=(1<<WDIE);
 

  Serial.println("Starting...");
  Serial.println("Input Char");
}

ISR(WDT_vect){
    Serial.println("Timeout...");
    digitalWrite(LED_PIN,LOW);
    flag=0;
}


void loop() {
  // put your main code here, to run repeatedly:
  char keyin;
  if(Serial.available()>0){
    digitalWrite(LED_PIN,HIGH);
    keyin=Serial.read();
    if(keyin=='x'){
      flag=1;
      while(flag);
    }
    else{
       delay(100);
       digitalWrite(LED_PIN,LOW);
    }
  }
  asm("WDR");
}

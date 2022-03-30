#include <avr/wdt.h>
#define TIMEOUT WDTO_4S
#define LED_PIN 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  wdt_enable(TIMEOUT);
  Serial.println("Rebooting...");
  Serial.println("Input Char");
}

void loop() {
  // put your main code here, to run repeatedly:
  char keyin;
  if(Serial.available()>0){
    digitalWrite(LED_PIN,HIGH);
    keyin=Serial.read();
    if(keyin=='x') while(1);
    else{
       delay(100);
       digitalWrite(LED_PIN,LOW);
    }
  }
  wdt_reset();
}

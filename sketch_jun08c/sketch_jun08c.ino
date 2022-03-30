#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#define Button 2
#define LED_PIN 13
int cnt=0;
volatile int f_wdt=0;


void myISR(){
  if(f_wdt==0) f_wdt=1;
  else Serial.println("WDT Overrun!!");
}


void enterSleep(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  
  sleep_disable();
  power_all_enable();

  digitalWrite(LED_PIN,LOW);
  delay(100);
  }
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("init...");
  delay(100);
  pinMode(LED_PIN,OUTPUT);
  pinMode(Button,INPUT_PULLUP);
  digitalWrite(LED_PIN,LOW);
  attachInterrupt(digitalPinToInterrupt(Button),myISR,LOW);
  Serial.println(7<<WDP0);
 MCUSR&=~(1<<WDRF);
  WDTCSR|=(1<<WDCE)|(1<<WDE);
   WDTCSR=1<<WDP2|1<<WDP1|1<<WDP0;
    WDTCSR|=(1<<WDIE); 
    Serial.println("init...complete");
    delay(100);
}

void loop() {

  // put your main code here, to run repeatedly:
if(f_wdt==1){
  digitalWrite(LED_PIN,HIGH);
  f_wdt=0;
  enterSleep();
}
}

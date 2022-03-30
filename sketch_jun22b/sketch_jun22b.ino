#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <wiring_private.h>
#define LED_PIN 13

int cnt=0;
int light=0;
volatile int ddc = 5 ;
volatile int t_step = 0 ;
volatile int f_wdt=1;
const int ttop = 24; 

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  randomSeed(analogRead(A0));
  
  pinMode(LED_PIN,OUTPUT);
  
  digitalWrite(LED_PIN,LOW);
  
  init_WDT();
  init_Timer1();

}



void loop() {
  // put your main code here, to run repeatedly:
  step1();
  step2();
}

void step1() {
  if(f_wdt == 1) {
    if(t_step==0){
      digitalWrite(LED_PIN,LOW);
      light=0;
      Serial.println("Step 1");
      ddc = random(2,50);
      Serial.print("Duty cycle = "); 
      Serial.println(ddc);
      delay(100);
      f_wdt=0;
      enterSleep();
    }
  }
}

void step2(){
  if(f_wdt == 1) {
    if(t_step==1){
      light=1;
      Serial.println("PWM...");
      delay(100);
      f_wdt=0;
    }
  }
}

void enterSleep() {
  Serial.println("Enter Sleep");
  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sleep_enable();
  sleep_mode();
  
  sleep_disable();
  power_all_enable();

}

//WDT 4s
void init_WDT(){
  MCUSR &= ~(1<<WDRF);  
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 1<<WDP3 ; //4秒  
  WDTCSR |= (1<<WDIE);
  Serial.println("init WDT...");
  delay(100);
}

//Timer1
void init_Timer1(){
  Serial.println("init Timer1...");
  delay(100);
  TCCR1A = 0;
  TCCR1B = (1<<WGM12); 
  TCCR1B |= (1<<CS10) | (1<<CS11);  
  OCR1A = ttop;  
  TCNT1=0;  
  TIMSK1 |= (1 << OCIE1A);
}

//看門狗
ISR(WDT_vect) { 
    if (t_step == 0 ){
        t_step = 1;
    }else{
        t_step = 0;
    }
    if(f_wdt == 0) f_wdt=1;
    Serial.println("Wakeup...");
}



//計數,每0.01秒呼叫一次
ISR(TIMER1_COMPA_vect){
    if( light == 1) {
      digitalWrite(LED_PIN,HIGH);
      cnt=cnt+1;
      //前ddc的方波為HIGH 
      if(cnt<ddc){
        digitalWrite(LED_PIN,HIGH);
      }
      //後ddc的方波為LOW
      if(cnt>ddc){
         digitalWrite(LED_PIN,LOW);
      }
      //超過100時,歸0
      if(cnt>100) {
        cnt=0;
      }
  }
}

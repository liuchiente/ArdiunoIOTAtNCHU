//5109056006 劉建德
#include <avr/wdt.h>
#define Buzzer 2 //指定蜂鳴器的接腳為D2
volatile int num=0;
volatile int count=0;
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(Buzzer,OUTPUT);       //設定蜂鳴器接腳為輸出模式
  //打開看門狗,4秒為timeout時間
  wdt_enable(WDTO_4S);
  //初始計數器
  SetupTimer();
}

void loop(){
}

//中斷計數器
void SetupTimer(){
  //初始暫存器
 TCCR2A=0;
 TCCR2B=0;
 TCNT2=0;
 
 //CTC模式
 TCCR2B=TCCR2B|(1<<3);

  //除頻和上限
 TCCR2B=TCCR2B|(1<<2);
 OCR2A=62.5;

 //致能中斷
 TIMSK2=TIMSK2|(1<<1);
}

//計數,每0.001秒呼叫一次
ISR(TIMER2_COMPA_vect){
  count=count+1;
  //當0.001*999大於999的時候就是1秒
  if(count>999){
    //產生亂數
    num=random(0,20); 
    Serial.println(num); 
    //歸零
    count=0;
    //當亂數為19
    if(num==19){
      while(1){
        //發出聲音
        play0();
        Serial.println("bee...."); 
      }
    }
    //定時清除看門狗
    wdt_reset();
  }
}

//發出聲音
void play0() {
  for(int i=0;i<10;i++) {
     digitalWrite(Buzzer,HIGH); delay(50);
    digitalWrite(Buzzer,LOW); delay(200);  
  } 
}

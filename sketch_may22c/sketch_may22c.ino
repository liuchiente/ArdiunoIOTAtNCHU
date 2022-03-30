//5109056006
#include "seg7.h"
//初始數字和記數
volatile int num=9527;
volatile int cnt=0;
void setup() {
  //初始化
  Serial.begin(9600);
  seg7_x4_init(2);
  randomSeed(analogRead(A0));
  //num=random(0,10000);
  SetupTimer();
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()) { 
  num=random(0,10000); 
  Serial.println(num); 
  Serial.read(); 
 }
}

void SetupTimer(){
  //初始暫存器 Time2
 TCCR2A=0;
 TCCR2B=0;
 TCNT2=0;
 
 //CTC模式
 TCCR2B=TCCR2B|(1<<3);

  //除頻和上限
 TCCR2B=TCCR2B|(1<<2);
 //設定0.0001秒
 OCR2A=62.5;
 //TCCR1B=TCCR1B|(1<<WGM12);

 //致能中斷
 TIMSK2=TIMSK2|(1<<1);
}

//中斷
ISR(TIMER2_COMPA_vect){
  display();  
}

//七段顯示器,每次顯示一個位元
void display(){
  //用來顯示1~4位數,mod 4確保控制位數在計數0~3
  //每次顯示一個位數
  cnt=cnt%4;
  //計算出10的幾次方,確保基底數為1~1000
  int bs=pow(10,cnt)+0.5;
  //用基底算出每個位數的數字,先除基底再mod 10
  int dig=num / bs % 10;
  //顯示該位數, 譬如位數0為7
  seg7_x4_display(cnt,dig);
  //累加計數器,顯示下一個位數
  cnt=cnt+1;
}

#include "seg7.h"
#define btn 10 //定義按鈕開關
int num=0;
int flag=0;

void setup() {
  // put your setup code here, to run once:
  seg7_x1_init(2); //初始化七段顯示器
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=2;i<8;i++){
      digitalWrite(i,HIGH);
      delay(1000);
      digitalWrite(i,LOW);
   }
}

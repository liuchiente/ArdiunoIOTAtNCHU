#include "seg7.h"
//可變電阻
const int potPin=A0;
//呼吸燈
const int ledPin=11;
//按鈕
const int btn=12;
//亂數
int innDer=-1;
//亂數
int gusS=0;
//暫存狀態
uint8_t state;
//flag
int brk=0;
void setup() {

  //初始化串列埠
  Serial.begin(9600);
  //初始化七段顯示器
  seg7_x1_init(2); 
  //按鈕
  pinMode(12,INPUT_PULLUP);
  //可變電阻
  pinMode(potPin,INPUT);
  //呼吸燈
  pinMode(ledPin,OUTPUT);
  
  seg7_x1_display(0);

  //按鈕
  uint8_t inBtn = digitalRead(12);
  
  //輸入數字
  while(innDer<0){
    while(Serial.available()>0){
       char inChar = Serial.read();
       if(inChar!=10){
          int inDex=(int)inChar-48;
          if(inDex>0&&inDex<10){
            innDer=inDex;
            seg7_x1_display(innDer);
            delay(2000);
          }else{
            //error
            Serial.println("input 0~9");
            innDer=-1;
          }
          Serial.println(inChar);
        }
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(innDer);

  //可變電阻
  int ctrl=analogRead(potPin);
  //延遲時間
  int ddelay=map(ctrl,0,1023,250,2000);
  Serial.print("Input ");
  Serial.println(ctrl);
  Serial.print("delay ");
  Serial.print(ddelay);
  Serial.println(" ms");
  Serial.println(" ");
  delay(ddelay);

  uint8_t bttn = digitalRead(12);

  if (bttn == LOW){
    //按下按鍵時,確定現在狀態
      Serial.println("ok");
    if(brk==0){
      brk=1;
    }else{
        brk=0;
        gusS=random(0,9);
        analogWrite(ledPin,0);
    }
    delay(50);
  }

    if(brk==1){
      //持續顯示
      seg7_x1_display(gusS);
      //相符
      if(gusS==innDer){
            for(int i=0;i<(255*0.1*innDer);i+=30){
              //Serial.println("MX "+i);
               analogWrite(ledPin,i);
                delay(250);
             }
            
            for(int i=(255*0.1*innDer);i>0;i-=30){
              //Serial.println("MI "+i);
               analogWrite(ledPin,i);
                delay(250);
             }
       } 
    }else{
       gusS=random(0,9);
    }
     //顯示變數
   seg7_x1_display(gusS);
  
}

//參考
int map(int x,int alow,int ahigh,int blow,int bhigh){
  float middle=ahigh/2;
  if(x>=ahigh-1) return bhigh;
  else if(x<=alow+1) return blow;
  else if(x>=middle) return x*2.682;
  else {
      return x*3.41;
    }
  return 1;
}

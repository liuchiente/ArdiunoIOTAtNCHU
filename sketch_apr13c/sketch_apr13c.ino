#include "seg7.h"
const int potPin=A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(potPin,INPUT);
  seg7_x1_init(2); //初始化七段顯示器
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;
  float valt;
  val=analogRead(potPin);
 // valt=val*0.00488;
  //Serial.print(val);
  //Serial.print("=>");
  //Serial.print(valt,1);
  //Serial.println('V');
  //delay(1000);
  int ddlay=map(val,0,1023,100,2000);
  Serial.println(val);
  Serial.println(ddlay);
  //Serial.println(ddlay);
   for(int i=2;i<8;i++){
      digitalWrite(i,HIGH);
      delay(ddlay);
      digitalWrite(i,LOW);
   }
}

int map(int x,int alow,int ahigh,int blow,int bhigh){
  if(x>=ahigh-1) return bhigh;
  else if(x<=alow+1) return blow;
  else {
      return x*0.5115;
    }
  return 1;
  }

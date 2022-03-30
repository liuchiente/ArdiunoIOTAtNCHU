#include "seg7.h"
int num=0;
int flag=0;
const int potPin=A0;
void setup() {
  // put your setup code here, to run once:
  seg7_x1_init(2); //初始化七段顯示器
  seg7_x1_display(0);
  pinMode(potPin,INPUT);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int num=random(0,9);
  int val;
  float valt;
  val=analogRead(potPin);
  seg7_x1_display(num);
  int ddy=map(val,0,1023,200,3000);
  Serial.print("Input ");
  Serial.println(val);
  Serial.print("delay ");
  Serial.print(ddy);
  Serial.println(" ms");
  Serial.println(" ");
  delay(ddy);
}

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

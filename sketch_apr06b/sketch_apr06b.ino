/**
 * 七段顯示器,每秒計數從0到9,無限循環
 * 2021/04
 */
#include "seg7.h"
void setup() {
  pinMode(btn,INPUT_PULLUP);
  seg7_x1_init(2); //初始化七段顯示器
  seg7_x1_display(0);
  Serial.begin(9600);
}

void loop() {
 for(int i=0;i<10;i++){
    //共陽極七段顯示器,請參考seg7.h檔
     seg7_x1_display_c(i);
      delay(1000);
    }
}

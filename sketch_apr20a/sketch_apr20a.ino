/**
 * 四位數七段顯示器
 * 2021/04
 */
void setup() {
  seg7_x4_init(2); //初始化七段顯示器
}

void loop() {
  while(1){
    delay(5);  
    seg7_x4_display(0,4);
    delay(5);
    seg7_x4_display(1,3);
    delay(5);
    seg7_x4_display(2,2);
    delay(5);
    seg7_x4_display(3,1);
  }  
}

const byte seg7_digit[10]={ B11111100,  //數字0
              B01100000,  //數字1
              B11011010,  //數字2
              B11110010,  //數字3
              B01100110,  //數字4
              B10110110,  //數字5
              B10111110,  //數字6
              B11100100,  //數字7
              B11111110,  //數字8
              B11110110}; //數字9
int seg7_x1_FirstPin;  //一位數七段顯示器的第一隻接腳
int seg7_x4_FirstPin;  //四位數七段顯示器的第一隻接腳

//*** 初始化四位數七段顯示器12隻連續的接腳
void seg7_x4_init(int pin) {
  seg7_x4_FirstPin=pin;  //設定四位數七段顯示器的第一隻接腳
  for(int i=0; i<12; i++) pinMode(seg7_x4_FirstPin+i, OUTPUT);
}

//*** 四位數七段顯示器顯示數字
void seg7_x4_display(int digit, int num) {
  byte mask;
  //共陰極七段顯示器,0 LOW為致能, 1 HIGH為、禁用
  //先關掉四顆七段顯示器
  for(int i=8; i<12; i++) digitalWrite(seg7_x4_FirstPin+i, HIGH);
  //再致能指定的七段顯示器
  switch(digit) {
    case 0: digitalWrite(seg7_x4_FirstPin+8, LOW); break;
    case 1: digitalWrite(seg7_x4_FirstPin+9, LOW); break;
    case 2: digitalWrite(seg7_x4_FirstPin+10, LOW); break;
    case 3: digitalWrite(seg7_x4_FirstPin+11, LOW); break;
  }
  //顯示數字
  for(int i=0; i<8; i++)  {
    mask=B10000000>>i;
    if(seg7_digit[num] & mask) digitalWrite(seg7_x4_FirstPin+i, HIGH);
    else digitalWrite(seg7_x4_FirstPin+i, LOW);
  }
}

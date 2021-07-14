/**
 * 設計一個按鈕開關,按一下燈就亮,再按一下燈就滅
 * 2021/04
 */
//計數器
int counter=0;
//防彈跳變數
int brk=0;
//暫存現在狀態
uint8_t state;
//啟動Arduino設定
void setup() {
  //第13隻腳位輸出
  pinMode(13,OUTPUT);
  //第2隻腳輸入,模式設為上拉電阻
  pinMode(2,INPUT_PULLUP);
  //先寫入第13隻腳為LOW
  digitalWrite(13,LOW);
  //初始化串列埠
  Serial.begin(9600);
  //給一個初始值
  state = digitalRead(2);
}


void loop() {
  //讀入
  uint8_t btn = digitalRead(2);
  //按下按鍵時
  if (btn == LOW&&brk==0){
    if( state == HIGH){
       state=LOW;
       digitalWrite(13,state);
     }else{
       state=HIGH;
       digitalWrite(13,state);
     }
     //防彈跳
     brk=1;
     //顯示計數值
     counter=counter+1;
     Serial.println(counter);
     delay(250);
  }
  
  brk=0;
}

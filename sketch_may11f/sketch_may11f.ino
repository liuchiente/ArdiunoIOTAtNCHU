//5109056006 劉建德 我是原著,從沒提供給別人用
//Col腳位
const byte colPins[4]={7,6,5,4};
//Row腳位
const byte rowPins[4]={11,10,9,8};
const char keymap[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};

byte i,j;
byte scanVal;

volatile unsigned long lastDebounceTime = 0; 
volatile unsigned long debounceDelay = 50; 

//輸出字元
char keyput;
//標記
int flag=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(i=0;i<=3;i++){
    //對輸入PIN初始化,設定中斷
    pciSetup(rowPins[i]);
    //設定腳位模式
    pinMode(rowPins[i],INPUT);
    pinMode(colPins[i],OUTPUT);
    //預設全寫入高電位
    digitalWrite(colPins[i],HIGH);
    digitalWrite(rowPins[i],HIGH);
  }
  //預設輸出空字元
  keyput='\0'; 
  //清空loop,改用計時器中斷來做
  //不用計時器的話,可能導致掃瞄鍵盤有異常 
  SetupTimer();
}

//參考官網做的中斷腳位設定
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

void loop() {
 //清空loop
}

//中斷
ISR(TIMER2_COMPA_vect){
   //持續掃瞄鍵盤
  scan();
  //持續確認有無輸出
  out();
}

//初始化計時器,每0.0001秒掃瞄鍵盤,監控輸出
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

 //致能中斷
 TIMSK2=TIMSK2|(1<<1);
}

//鍵盤中斷
ISR (PCINT0_vect){
  //轉呼叫鍵盤程式
  kyboard();
  //紀錄當下時間,防彈跳
  lastDebounceTime=millis();
}

//掃瞄鍵盤
void scan(){
 for(i=0;i<=3;i++){  
    for(j=0;j<=3;j++){
      //行寫入低電位,列寫入高電位,持續檢查有無按下按鍵短路
       digitalWrite(rowPins[i],HIGH);
       digitalWrite(colPins[j],LOW);
    }
  }
}

void out(){
//當有輸出時,類似佇列
  if(keyput!='\0'){
    if((millis() - lastDebounceTime) > debounceDelay){   
      Serial.println(keyput);
      //輸出完畢改為空字元
      keyput='\0';
    }
  }  
}

// 中斷呼叫鍵盤程式
void kyboard(){
  for(i=0;i<=3;i++){
    for(j=0;j<=3;j++){
      digitalWrite(colPins[j],LOW);
      scanVal=digitalRead(rowPins[i]);
        if(scanVal==LOW){
          keyput=keymap[i][j];
          //Serial.println(keymap[i][j]);  // 輸出按鍵代表的字元
          digitalWrite(colPins[j], HIGH);
          flag=1;
          break;
        }
        digitalWrite(colPins[j], HIGH);
    }
  }
}

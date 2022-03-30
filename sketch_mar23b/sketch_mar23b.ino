void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

  
void loop() {
  // put your main code here, to run repeatedly:
  //猜中次數
  int q_size=0;
  int b_size=0;
  //3位元陣列,預設數字456
  char message[4] = "456";
  String input = "";
  int i_guess=0;
    while(Serial.available()>0){
       char inChar = Serial.read();
       input+=inChar;
       //只抓取前3字元
       if(i_guess<3){
        //判斷三個字元的猜測狀況
         for(int i=0;i<3;i++){
          //先確認有沒有猜中A的
          if(i==i_guess&&message[i]==inChar){
              q_size=q_size+1;
            }else if(message[i]==inChar){
               //確認有沒有猜中B的 //確認有沒有猜中B的
              b_size=b_size+1;
              } 
         } 
         //每抓到一個輸入就累加1
         i_guess=i_guess+1;
       }
    }
    
    if(i_guess>0){
      //當有輸入時,才印出判斷結果
     Serial.println("input : "+input+"result :"+q_size+"A "+b_size+"B");
    }
  
  delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int char_size=0;
  int word_size=0;
  int last=0;
  while(Serial.available()>0){
     int inByte = Serial.read();
     
     if(inByte!=10){
        char_size=char_size+1;
     }
      
    if(inByte!=32&&last==0){
        word_size=word_size+1;
        last=inByte;
     }else if(inByte==32){
        last=0;
      }
     
  }
  Serial.println("==I got==");
  Serial.println(char_size);
  Serial.println(word_size);
  delay(2000);
}

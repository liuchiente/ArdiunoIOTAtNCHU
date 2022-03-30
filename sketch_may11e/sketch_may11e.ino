#define LedPin 13
#define ButtonPin 2

int step_num=0;
int flag=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin,OUTPUT);
  pinMode(ButtonPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ButtonPin),my_ISR,FALLING);
  Serial.begin(9600);
  Serial.println(step_num);
}

void loop() {
  if(flag==1){
     Serial.println(step_num);
     flag=0;
     delay(1000);
    }
}

void my_ISR(){
  if(flag==0){
    flag=1;
     step_num=step_num+1;
  }
 
 


}

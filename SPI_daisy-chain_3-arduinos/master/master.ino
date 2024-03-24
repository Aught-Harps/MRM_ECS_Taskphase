
#include <SPI.h>
volatile int MasterRecieve;
volatile int MasterSend = 0;
int button1 = 2;
int button2 = 3;
int led1 = 7;
int led2 = 8;


void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(SS,OUTPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(7, OUTPUT);

}

void loop() {
  digitalWrite(SS,LOW);
  int push1= digitalRead(2);
  int push2= digitalRead(3);

  if (push1 ==HIGH){
    MasterSend = 101;
    
  }
  if (push1 ==LOW){
    MasterSend = 110;
    Serial.println(" on");
  }
  MasterRecieve = SPI.transfer(MasterSend);
  Serial.print(MasterRecieve);
  Serial.print(",");

  //recieved from slave
  if ((MasterRecieve == 21) || (MasterRecieve == 3) ){
    digitalWrite(7, HIGH);
    Serial.print("ledON");
    Serial.print(",");
  }
  if ((MasterRecieve == 30) || (MasterRecieve == 12) ){
    digitalWrite(7, LOW);
  }

  if ((MasterRecieve == 12) || (MasterRecieve == 3) ){
    digitalWrite(8, HIGH);
    Serial.print("ledON");
    Serial.print(",");
  }
  if ((MasterRecieve == 30) || (MasterRecieve == 21) ){
    digitalWrite(8, LOW);
  }

  if (push2 ==HIGH){
    MasterSend = 201;
  }
  if (push2 ==LOW){
    MasterSend = 210;
  }  
  MasterRecieve = SPI.transfer(MasterSend);
  Serial.println(MasterRecieve);


  


  digitalWrite(SS,HIGH);

}

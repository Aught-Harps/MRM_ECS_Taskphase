///AUTHOR: Harsh Gupta
////2-Arduino-SPI MASTER CODE

#include<SPI.h>                             
#define LED 4
#define LED2 5
 
#define button1 2
#define button2 3

const int slave2= 9;

int x;
int pushvalue;
int pushvalue2;
int data;
int data2;
volatile int Mastereceive;
volatile int Mastereceive2;

void setup()
{
  Serial.begin(9600);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);

  pinMode(LED,OUTPUT);
  pinMode(LED2,OUTPUT);

  SPI.begin();            
  pinMode(SS,HIGH);
  pinMode(slave2,HIGH);
  pinMode(MISO,INPUT);
  pinMode(MOSI, OUTPUT);

}

void loop(void)
{
  ////slave1

  digitalWrite(SS,LOW);
  int Mastersend = 200;                            
  
  int pushvalue = digitalRead(2);


  if (pushvalue == LOW){
    Mastereceive=SPI.transfer(Mastersend); 
    delay(100);
    Serial.println(Mastereceive);
  }

  else {
    int Mastersend2 = 0;
    Mastereceive=SPI.transfer(Mastersend2); 
    delay(100);
    Serial.println(Mastereceive);
  }

  //digitalWrite(SS,HIGH);
  //digitalWrite(9,LOW);


  if (Mastereceive==105){
    digitalWrite(8,HIGH);
  }
  else digitalWrite(8, LOW);


  digitalWrite(SS,HIGH);


  digitalWrite(slave2,LOW);

  //button 2
  int push2 = digitalRead(3);
  
  if (push2 == LOW){
    int data2 = 5;
    Mastereceive2=SPI.transfer(data2); 
    delay(100);
    Serial.println(Mastereceive2);
  }

  else if (push2 ==HIGH){
    int data2 = 6;
    Mastereceive2=SPI.transfer(data2); 
    delay(100);
    Serial.println(Mastereceive2);
  }

  digitalWrite(slave2,HIGH);


  if (Mastereceive == 105){
    digitalWrite(7,HIGH);
  }

  if (Mastereceive2 == 106){
    digitalWrite(6,HIGH);
  }

  if (Mastereceive!=105){
    digitalWrite(7,LOW);
    

  }

  if (Mastereceive2!=106){
    digitalWrite(6,LOW);

  }


  
}
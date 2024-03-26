///AUTHOR: HARSH
//Slave arduino
/// 1 master and 1 slave button-LED configuration
#include<SPI.h>

#define LEDpin 8
#define button 2

volatile boolean received;
volatile byte Slavereceived,Slavesend;
bool pushvalue;
int x;

void setup()
{
  
  Serial.begin(9600);
  pinMode(SS, INPUT);
  pinMode(MISO, OUTPUT);
  
  pinMode(button,INPUT_PULLUP);               
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);                 
  SPCR |= _BV(SPE); 
  SPCR |= _BV(SPIE);                      
  received = false;

  SPI.attachInterrupt();                  
  
}

ISR (SPI_STC_vect)                        
{
  Slavereceived = SPDR;
  Serial.println(Slavereceived)   ;      
  received = true;                        
}

void loop()
{ 
  pushvalue=digitalRead(2); 
  if(received)                            
  {     
   if (Slavereceived == 200 || Slavereceived == 0){

    if (pushvalue==LOW){
      SPDR = 105;
    }

    if (Slavereceived == 200){
      digitalWrite(8,HIGH);
    }

    if (Slavereceived == 0){
      digitalWrite(8,LOW);
    }
    
   }

   if (Slavereceived == 5 || Slavereceived==6){
    if (pushvalue==LOW){
      SPDR = 106;
    }

    if (Slavereceived == 5){
      digitalWrite(7,HIGH);
    }

    if (Slavereceived == 6){
      digitalWrite(7,LOW);
    }
   }

   SPDR = 0;

  }
}
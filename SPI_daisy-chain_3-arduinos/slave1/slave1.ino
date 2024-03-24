///slave1 --- daisy chain

#include <SPI.h>
int pushvalue= HIGH;
int button = 2;
int led = 7;

volatile byte Slavereceived;
volatile bool received = false;


void setup(){
  Serial.begin(9600);
  SPI.begin();

  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  SPCR |= _BV(SPE); 
  SPCR |= _BV(SPIE);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS,INPUT);

  received = false;   
  SPI.attachInterrupt();
}


ISR (SPI_STC_vect)                        
{
  Slavereceived = SPDR;
  Serial.println(Slavereceived);      
  received = true;                        
}

void loop(){
  if (received){
    Serial.println("slave1 recieved");

    SPDR = Slavereceived;
  }

}
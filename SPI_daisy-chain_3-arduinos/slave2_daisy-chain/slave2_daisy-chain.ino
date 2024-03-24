///slave2 --- daisy chain

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
  pinMode(3, INPUT_PULLUP);

  pinMode(led, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(5, OUTPUT);

  SPCR |= _BV(SPE); 
  //SPCR |= _BV(SPIE);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS,INPUT);

  received = false;
  SPI.attachInterrupt();
}


ISR (SPI_STC_vect)                        
{
  Slavereceived = SPDR;
  //Serial.print(Slavereceived);      
  received = true;                        
}

void loop(){
  //digitalWrite(8,HIGH);
  
  bool push = digitalRead(button);
  bool push2 = digitalRead(3);
  int x;
  int y;
  if (received){
    //Serial.println("slave2 recieved");
    Serial.print(",");
    Serial.println(Slavereceived);


    if (Slavereceived==210){
      digitalWrite(7,HIGH);
    }
    if (Slavereceived==201){
      digitalWrite(7,LOW);
    }


    if (Slavereceived==110){
      digitalWrite(8,HIGH);
    }
    if (Slavereceived==101){
      digitalWrite(8,LOW);
    }

    //slavesend code--- dont touch 
    if (push == LOW){
      Serial.print("HIGH");
      x = 1;
    }
    if (push == HIGH){
      Serial.print("LOW");
      x = 10;
    }

    if (push2 == LOW){
      Serial.print("HIGH");
      y = 2;
    }
    if (push2 == HIGH){
      Serial.print("LOW");
      y = 20;
    }

  int z = x + y;
  SPDR = z;

  }

}
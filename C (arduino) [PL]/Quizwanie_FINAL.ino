#include <ShiftRegister74HC595.h>
#include <PCF8574.h>
#include <Wire.h>
PCF8574 expander;

  /*---------------------------------------DEKLARACJE ZMIENNYCH---------------------------------------*/

int latchPin1 = 0;  //WYSWIETLACZ CZERWONY JEDNOSCI
int dataPin1 = 1;
int clockPin1 = 2; 

int latchPin2 = 0; // WYSWIETLACZ CZERWONY DZIESIATKI
int dataPin2 = 3;
int clockPin2 = 4;

int latchPin3 = 0; // WYSWIETLACZ ZIELONY DZIESIATKI
int dataPin3 = 5;
int clockPin3 = 6;

int latchPin4 = 0; // WYSWIETLACZ ZIELONY JEDNOSCI
int dataPin4 = 7;
int clockPin4 = 8;

int pa = 0;  //Duze przyciski
int pb = 0;
int blok = 0;

int i=0; int x=0; int j1; int d1; int j2; int d2;  //Wyswietlacze
int jednosci[] = {64,121,36,48,25,18,2,120,0,24};
int dziesiatki[] = {64,121,36,48,25,18,2,120,0,24};

int bazzer=0;

  /*---------------------------------------OZNACZENIE PINOW I ICH OBSLUGA---------------------------------------*/

void setup() {

 //  Serial.begin(9600);

  expander.begin(0x38);
  expander.pinMode(0, INPUT_PULLUP); //przycisk czerwony wyswietlacz ++
  expander.pullUp(0);
  expander.pinMode(1, INPUT_PULLUP); //przycisk czerwony wyswietlacz --
  expander.pullUp(1);
  expander.pinMode(2, INPUT_PULLUP); //przycisk żółty JESZCZE NIE GOTOWY!!!
  expander.pullUp(2);
  expander.pinMode(3, INPUT_PULLUP); //przycisk reset 
  expander.pullUp(3);
  expander.pinMode(4, INPUT_PULLUP); //przycisk żółty JESZCZE NIE GOTOWY!!! 
  expander.pullUp(4);

  
  pinMode(latchPin1, OUTPUT); // Wyswietlacze 3 i 4 JESZCZE NIE GOTOWY!!!
  pinMode(dataPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(latchPin3, OUTPUT);
  pinMode(dataPin3, OUTPUT);
  pinMode(clockPin3, OUTPUT);
  pinMode(latchPin4, OUTPUT);
  pinMode(dataPin4, OUTPUT);
  pinMode(clockPin4, OUTPUT);
  
  pinMode(9, INPUT_PULLUP); // Przycisk duzy 1
  pinMode(11, INPUT_PULLUP); // Przycisk duzy 2
  
  pinMode(10, OUTPUT); // Swiatlo 1
  pinMode(12, OUTPUT); // Swiatlo 2
  pinMode(13, OUTPUT); //Bazzer
  
  digitalWrite(10, LOW); //Stan poczatkowy swiatlo duzego przycisku
  digitalWrite(12, LOW); //Stan poczatkowy swiatlo duzego przycisku
  digitalWrite(13, LOW); //Stan poczatkowy bazzer
  

}




void loop() {

  /*---------------------------------------WYSWIETLACZ---------------------------------------*/
   d1=i/10;  
   j1=i%10;
   jednosci[j1];
   dziesiatki[d1];

   digitalWrite(latchPin1, LOW);                          //RYSOWANIE WYSWIETLACZ CZERWONY DZIESIATKI
   shiftOut(dataPin1, clockPin1, MSBFIRST, dziesiatki[d1]);
   digitalWrite(latchPin1, HIGH);


   digitalWrite(latchPin2, LOW);                          //RYSOWANIE WYSWIETLACZ CZERWONY JEDNOSCI
   shiftOut(dataPin2, clockPin2, MSBFIRST, jednosci[j1]);
   digitalWrite(latchPin2, HIGH);

   d2=x/10;  
   j2=x%10;
   jednosci[j2];
   dziesiatki[d2];
   
   digitalWrite(latchPin3, LOW);                          //RYSOWANIE WYSWIETLACZ ZIELONY DZIESIATKI
   shiftOut(dataPin3, clockPin3, MSBFIRST, dziesiatki[d2]);
   digitalWrite(latchPin3, HIGH);


   digitalWrite(latchPin4, LOW);                          //RYSOWANIE WYSWIETLACZ ZIELONY JEDNOSCI
   shiftOut(dataPin4, clockPin4, MSBFIRST, jednosci[j2]);
   digitalWrite(latchPin4, HIGH);


/*---------------------------------------PRZYCISKI DUZE---------------------------------------*/


   if ((digitalRead(9) == HIGH) && (digitalRead(11) == HIGH) && (blok==0)) {   //Przycisk duzy niebieski
     pa=1;
     blok=1;
     pb=0;
     bazzer=1;
   } 
   digitalWrite(10, pa); 
   
    if (bazzer == 1){
      digitalWrite(13, HIGH); 
      delay(1000);
      bazzer=0;
      digitalWrite(13, LOW); 
    }

  
   if ((digitalRead(9) == LOW) && (digitalRead(11) == LOW) && (blok==0)) {    //Przycisk duzy zielony
     pa=0;
     blok=1;
     pb=1;
     bazzer=1;
   }
   digitalWrite(12, pb); 
   digitalWrite(13, bazzer); 
   
       if (bazzer == 1){
      digitalWrite(13, HIGH); 
      delay(1000);
      bazzer=0;
      digitalWrite(13, LOW); 
    }



   if (expander.digitalRead(3) == LOW){   // Reset swiatla przycisku duzego
  pa=0;
  blok=0;
  pb=0;
  }

/*---------------------------------------PRZYCISKI MAŁE PUNKTACJA---------------------------------------*/

  if (expander.digitalRead(0) == LOW){ //Jeśli przycisk jest wciśnięty 
    delay(250);
  i++;
  }
  
  if (expander.digitalRead(1) == LOW){ //Jeśli przycisk jest wciśnięty 
    delay(250);
  i--;
  }

   if (expander.digitalRead(2) == LOW){ //Jeśli przycisk jest wciśnięty 
    delay(250);
  x++;
  }
  
  if (expander.digitalRead(4) == LOW){ //Jeśli przycisk jest wciśnięty 
    delay(250);
  x--;
  }
}

#include <QMC5883L.h>

QMC5883L compass;

void setup()
{

/********************************KOMPAS********************************/
  
	compass.init();
	compass.setSamplingRate(50);

	Serial.begin(9600);
	Serial.println("QMC5883L Compass Demo");
	Serial.println("Turn compass in all directions to calibrate....");


 /********************************DIODY********************************/
  pinMode(10, OUTPUT); 
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
}

/********************************KOMPAS********************************/

void loop()
{
	
		int heading = compass.readHeading();
		if(heading==0) {
			/* Still calibrating, so measure but don't print */
		} else {
			Serial.println(heading);
		}
	
/********************************DIODY********************************/

   if (( heading >= 293) && (heading<338)) { digitalWrite(3,HIGH); delay(10);}
    if ((( heading >= 338 ) && (heading< 360)) || (( heading >= 0 ) && (heading < 22))) { digitalWrite(2,HIGH); delay(10);}
     if (( heading >= 22 ) && (heading< 68)) { digitalWrite(10,HIGH); delay(10);}
      if (( heading >= 248) && (heading< 293)) { digitalWrite(6,HIGH); delay(10);}
       if (( heading >= 68 ) && (heading<123 )) { digitalWrite(4,HIGH); delay(10);}
        if (( heading >= 203) && (heading<248)) { digitalWrite(9,HIGH); delay(10);}
         if (( heading >= 158) && (heading<203)) { digitalWrite(8,HIGH); delay(10);}
          if (( heading >= 123) && (heading<158)) { digitalWrite(7,HIGH); delay(10);}

     
          digitalWrite(9,LOW);
          digitalWrite(8,LOW);
          digitalWrite(7,LOW);
          digitalWrite(6,LOW);
          digitalWrite(5,HIGH);
          digitalWrite(4,LOW);
          digitalWrite(3,LOW);
          digitalWrite(2,LOW);
          digitalWrite(10,LOW);		

          
	}

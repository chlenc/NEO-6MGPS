/*********************
 *10 to GPS Module TX*
 *09 to GPS Module RX*
 *********************/

#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial mySerial(10, 11);
TinyGPS gps;

void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);

uint32_t counter = 0;

void setup()  
{
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);
}

void loop() 
{
  bool newdata = false;
  unsigned long start = millis();
  // Every 5 seconds we print an update
  while (millis() - start < 5000) 
  {
    if (mySerial.available()) 
    
    {
      char c = mySerial.read();
      if (gps.encode(c)) 
      {
        newdata = true;
        break;  
      }
    }
  }
  
  if (newdata) {
    gpsdump(gps);
  }
}

void gpsdump(TinyGPS &gps)
{
  long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  gps.f_get_position(&flat, &flon, &age);
  Serial.print(counter++); 
  Serial.print(": "); 
  printFloat(flat, 5); 
  Serial.print(", ");
  printFloat(flon, 5);
  Serial.println();
}

void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0) 
  {
     Serial.print('-');
     number = -number;
  }

  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0) 
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}

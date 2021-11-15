#include <LiquidCrystal.h>

#include <TinyGPS.h>

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);


TinyGPS gps;


void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    { char c = Serial.read();
     
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    lcd.clear();
    lcd.print("LAT:");
    lcd.print(flat, 5);

    lcd.setCursor(0, 1);
    lcd.print("LON:");
    lcd.print(flon, 5);
    
  }
  
  gps.stats(&chars, &sentences, &failed);
  delay(3000);
}

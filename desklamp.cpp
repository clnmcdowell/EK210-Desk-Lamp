#include <Adafruit_NeoPixel.h>

#define led 6
#define power 8
#define button 2
#define ledCount 16
#define slide A0
int on, buttonPress, count = 0;
int morningLength = 10; //in seconds 
int morningCount = (morningLength / 0.01544);
int nightLength = 5; //in seconds
int nightCount = (nightLength / 0.01544);
double aread, brightness;
double minBright = 50; //minimum brightness between 0 and 255
double x = (((minBright / 255.0) * 1023) - 469) / (1 - (minBright / 255.0));

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ledCount, led, NEO_RGBW + NEO_KHZ800);

void setup() {
 pixels.begin();
 pinMode(power, INPUT);
 pinMode(button, INPUT);
 Serial.begin(9600);
}
 
void loop() {
  on = digitalRead(power);
  aread = analogRead(slide);
  brightness = ((aread + x)/(1023 + x))* 255; //formula to covert analog signal to brightness value out of 255
  count++;
  
  while(on == HIGH && count < morningCount)
  { 
   
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness,brightness,brightness,0)); //full spectrum white light
      pixels.show(); 
    }
    on = digitalRead(power);
    
    aread = analogRead(slide);
    brightness = ((aread + x)/(1023 + x))* 255;

    count++;

    buttonPress = digitalRead(button);
    if(buttonPress == HIGH)
    {
      while(buttonPress == HIGH)
      {
        buttonPress = digitalRead(button);
      }
      
      count = morningCount;
    }
  }

  while(on == HIGH && count >= morningCount && count <= (morningCount + nightCount))
  { 
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0,brightness));
      pixels.show(); 
    }
    on = digitalRead(power);
    
    aread = analogRead(slide);
    brightness = ((aread + x)/(1023 + x))* 255;

    if(count == (morningCount + nightCount))
    {
      count = 0;
    }

    count++;

    buttonPress = digitalRead(button);

    if(buttonPress == HIGH)
    {
      while(buttonPress == HIGH)
      {
        buttonPress = digitalRead(button);
      }
      
      count = 0;
    } 
  }

  while(on == LOW)
  {
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0,0));
      pixels.show();
    }

    on = digitalRead(power);
    count++;
    
    if(count == (morningCount + nightCount))
    {
      count = 0;
    }
  }
}

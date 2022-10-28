#include <Adafruit_NeoPixel.h>

#define led 6
#define power 8
#define button 4
#define ledCount 16
#define slide A0
int on, count = 0;
int morningLength = 10000; //in ms
int nightLength = 5000;
double aread, brightness;
double minBright = 50; //minimum brightness between 0 and 255
double x = (((minBright / 255.0) * 1023) - 469) / (1 - (minBright / 255.0));

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ledCount, led, NEO_RGBW + NEO_KHZ800);

void setup() {
 pixels.begin();
 
 pinMode(power, INPUT);
 pinMode(button, INPUT);
}
 
void loop() {
  on = digitalRead(power);
  aread = analogRead(slide);
  brightness = ((aread + x)/(1023 + x))* 255; //formula to covert analog signal to brightness value out of 255
  
  while(on == HIGH && count < morningLength)
  { 
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0,brightness)); //warm white light
      pixels.show(); 
      on = digitalRead(power);
    }
    aread = analogRead(slide);
    brightness = ((aread + x)/(1023 + x))* 255;
    if(button == HIGH)
      count = morningLength;
   
    count++;
  }

  while(on == HIGH && count > morningLength && count <= nightLength)
  { 
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness,brightness,brightness,0)); //full spectrum white light
      pixels.show(); 
      on = digitalRead(power);
    }
    aread = analogRead(slide);
    brightness = ((aread + x)/(1023 + x))* 255;
    if(count == nightLength || button == HIGH)
      count = 0;
   
    count++;
    
  }

  while(on == LOW)
  {
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0,0));
      pixels.show();
      on = digitalRead(power);
    }
    
    count++;
  }
}

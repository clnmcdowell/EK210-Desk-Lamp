#include <Adafruit_NeoPixel.h>

#define led 6
#define power 8
#define button 4
#define ledCount 16
#define slide A0
int on, buttonPress, count = 0;
int morningLength = 50400; //in seconds 
int morningCount = (morningLength / 0.01544); //converts seconding into time required to increment counter
int nightLength = 36000; //in seconds
int nightCount = (nightLength / 0.01544);//converts seconding into time required to increment counter
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
  on = digitalRead(power); //read if power switch is on
  
  aread = analogRead(slide); //read slider value
  brightness = ((aread + x)/(1023 + x))* 255; //formula to covert analog signal to brightness value out of 255
  count++;

  //while switch is on and in morning mode
  while(on == HIGH && count < morningCount) 
  { 
   
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness,brightness,brightness,0)); //set LEDs to full spectrum white light
      pixels.show(); 
    }
    on = digitalRead(power); 
    
    aread = analogRead(slide);
    brightness = ((aread + x)/(1023 + x))* 255;

    count++; //increment counter

    buttonPress = digitalRead(button);
    if(buttonPress == HIGH) //if button is pressed 
    {
      while(buttonPress == HIGH) //pause until button is released
      {
        buttonPress = digitalRead(button);
      }
      
      count = morningCount; //set counter to start of night mode
    }
  }

  //while switch is on and in night mode
  while(on == HIGH && count >= morningCount && count <= (morningCount + nightCount)) 
  { 
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0,brightness)); //set LEDs to warm white light
      pixels.show(); 
    }
    on = digitalRead(power);
    
    aread = analogRead(slide);
    brightness = ((aread + x)/(1023 + x))* 255;

    if(count == (morningCount + nightCount)) //if the end of the day night cycle is reached reset counter to 0
    {
      count = 0;
    }

    count++;

    buttonPress = digitalRead(button);
    if(buttonPress == HIGH) //if button is pressed
    {
      while(buttonPress == HIGH) //pause until button is released
      {
        buttonPress = digitalRead(button);
      }
      
      count = 0; //set counter to start of day night cycle
    } 
  }

  //while switch is off
  while(on == LOW)
  {
    for(int i = 0; i < ledCount; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0,0)); //set LED to ogg
      pixels.show();
    }

    on = digitalRead(power); //check if switch is turned on
    count++; //continue counter incrementing while light is off
    
    if(count == (morningCount + nightCount)) //if end of day night of day night cycle is reached reset counter to 0
    {
      count = 0;
    }
  }
}

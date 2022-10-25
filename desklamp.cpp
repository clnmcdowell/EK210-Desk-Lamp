#include <Adafruit_NeoPixel.h>

#define led 6
#define power 8
#define button 4
#define ledCount 16
#define slide A0
int on;
double aread,brightness, x = (-13689.0/41.0);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ledCount, led, NEO_RGBW + NEO_KHZ800);

void setup() {
 pixels.begin();
 
 pinMode(power, INPUT);
 pinMode(button, INPUT);
}
 
void loop() {
  on = digitalRead(power);
  aread = analogRead(slide);
  brightness = ((aread + x)/(1023+ x))*255;
  

if(on == HIGH){ 
 for(int i = 0; i < ledCount; i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0,brightness));
    pixels.show(); 
    on = digitalRead(power);
 }
}

if(on == LOW){
  for(int i = 0; i < ledCount; i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0,0));
    pixels.show();
    on = digitalRead(power);
 }
}
}

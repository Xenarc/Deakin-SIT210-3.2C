/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "g:/Mark/Documents/DOCUMENTS/Deakin/SIT210_Embedded_Systems_Development/3.2C/3-2C/src/3-2C.ino"
#include "..\lib\BH1750\src\BH1750.h"
#include <Wire.h>
bool Publish(const String message);
void setup();
void loop();
#line 3 "g:/Mark/Documents/DOCUMENTS/Deakin/SIT210_Embedded_Systems_Development/3.2C/3-2C/src/3-2C.ino"
BH1750 lightMeter;

const int SunnyThreshold = 300;
bool isSunny = false;
int suntimeCounter = 0;
const int frequency = 2500;

bool Publish(const String message){
  Serial.println(message);
  return Particle.publish("MBlashkiArgon_Sunlight", message, PRIVATE);
}

void setup(){

  Serial.begin(9600);
  Serial.println(F("Ready"));

  Wire.begin();

  lightMeter.begin();
  lightMeter.switch_power_on();
  Serial.println(F("BH1750 Setup"));
}

void loop() {
  float lux = lightMeter.get_light_level();
  
  if(isSunny){
    suntimeCounter++;
  }
  
  if(isSunny && lux < SunnyThreshold){
    // Not sunny -> sunny
    String message = "turned shady. It was in the sun for ";
    message.concat(suntimeCounter*frequency/1000/60);
    message.concat(" minutes");
    Publish(message);
    isSunny = false;
    suntimeCounter = 0;
  }
  else if(!isSunny && lux >= SunnyThreshold){
    // Sunny -> not sunny
    Publish("turned sunny");
    isSunny = true;
  }
  delay(frequency);
}

#include <Arduino.h>

// Configurations
const int startPin = 2;
const int endPin = 13;
const int speed = 80;
const int tailLength = 6;
const int maxBrightness = 255;

// States
int currentPin = startPin;
bool goRight = true;

void setup() {
  for(int thisPin = startPin; thisPin <= endPin; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void loop() {
  for (int length = tailLength; length > 0; length--) {
    int tailBrightness = length == tailLength ? maxBrightness : ((maxBrightness / 20) / tailLength) * length;
    int tailPinLocation = 0;

    if (goRight) {
      tailPinLocation = currentPin - (tailLength - length);
    } else {
      tailPinLocation = currentPin + (tailLength - length);
    }
   
    if (tailPinLocation >= startPin && tailPinLocation <= endPin) {
      analogWrite(tailPinLocation, tailBrightness);
    }
  }

  if (currentPin >= endPin) {
    analogWrite(endPin, maxBrightness);
  } else if (currentPin <= startPin) {
    analogWrite(startPin, maxBrightness);
  }

  int clearUpPin = 0;

  if (goRight) {
    clearUpPin = currentPin - tailLength;
    currentPin++;
  } else {
    clearUpPin = currentPin + tailLength;
    currentPin--;
  }

  if (clearUpPin >= startPin && clearUpPin <= endPin) {
    analogWrite(clearUpPin, 0);
  }

  if (currentPin + tailLength <= startPin) {
    goRight = true;
  } else if (currentPin - tailLength >= endPin) {
    goRight = false;
  }

  delay(speed);
}

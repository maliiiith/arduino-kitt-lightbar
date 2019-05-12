#include <Arduino.h>

// Configurations
int startPin = 2;
int endPin = 13;
int speed = 40;
int tailLength = 4;
int maxBrightness = 255;

void draw(int pin, bool leftTail = true);

void setup() {
  for(int thisPin = startPin; thisPin <= endPin; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void loop() {
  for (int i = startPin; i <= endPin; i++) {
    draw(i, false);
  }

  for (int i = endPin; i >= startPin; i--) {
    draw(i);
  }
}

void draw(int pin, bool leftTail = true) {
  for (int length = tailLength; length > 0; length--) {
    int brightness = length == tailLength ? maxBrightness : ((maxBrightness / 4) / tailLength) * length;
    if (leftTail) {
      int tailPinLocation = pin + (tailLength - length);
      if (tailPinLocation <= endPin) {
        analogWrite(tailPinLocation, brightness);
      }
    } else {
      int tailPinLocation = pin - (tailLength - length);
      if (tailPinLocation >= startPin) {
        analogWrite(tailPinLocation, brightness);
      }
    }
  }

  if (leftTail) {
    int clearUpBehind = pin - tailLength;
    if (clearUpBehind <= endPin) {
      analogWrite(pin + tailLength, 0);
    }
  } else {
    int clearUpBehind = pin - tailLength;
    if (clearUpBehind >= startPin) {
      analogWrite(pin - tailLength, 0);
    }
  }
  delay(speed);
}
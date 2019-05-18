#include <Arduino.h>

// Configurations
const int startPin = 2;
const int endPin = 13;
const int speed = 500;
const int tailLength = 4;
const int maxBrightness = 100;

// States
int currentPin = startPin;
bool goRight = true;
int drawPath[tailLength];

int *generatePath(int *path);

void setup() {
  Serial.begin(9600);
  for(int thisPin = startPin; thisPin <= endPin; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void loop() {
  generatePath(drawPath);
  for (int pin = 1; pin <= tailLength; pin++) {
    int tailBrightness = pin == tailLength ? maxBrightness : ((maxBrightness / 20) / tailLength) * pin;
    int tailPinLocation = drawPath[pin - 1];
    Serial.println(tailPinLocation);

    if (tailPinLocation >= startPin && tailPinLocation <= endPin) {
      analogWrite(tailPinLocation, tailBrightness);
    }
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

  delay(speed);
}

int *generatePath(int *path) {
  bool travelRight = path[0] < endPin;

  for (int i = 0; i < tailLength; i++) {
    int currentVal = path[i];
    if (path[i] == endPin) {
      travelRight = false;
    } else if (path[i] == startPin) {
      travelRight = true;
    }

    if (travelRight) {
      currentVal++;
    } else {
      currentVal--;
    }

    path[i] = currentVal;
  }

  return path;
}
#include <SoftwareSerial.h>
#include <Bounce2.h>

const int potentiometerPins[] = {A0, A1, A2, A3, A4};
const int muteButtonPins[] = {2, 3, 4, 5, 6};
const int numPots = 5;

Bounce debouncer[numPots];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numPots; i++) {
    pinMode(potentiometerPins[i], INPUT);
    debouncer[i] = Bounce();
    debouncer[i].attach(muteButtonPins[i], INPUT_PULLUP);
    debouncer[i].interval(5);
  }
}

void loop() {
  int potValues[numPots];
  for (int i = 0; i < numPots; i++) {
    potValues[i] = analogRead(potentiometerPins[i]);
    debouncer[i].update();
    if (debouncer[i].fell()) {
      potValues[i] = 0;  // Set the pot value to 0 when the button is pressed
    }
  }

  for (int i = 0; i < numPots; i++) {
    Serial.print(potValues[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}

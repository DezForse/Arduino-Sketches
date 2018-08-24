#include "OneButton.h"

int count = 7; // Start pins from 8
const int MIN_COUNT = 8; // Pin start
const int MAX_COUNT = 13; // Pin end
static int currentAction = LOW; // Dynamic action for led flashing
int leds[6]; // List of flashing leds

OneButton buttonLeft(2, true);  // Down button
OneButton buttonRight(3, true); // Up button
OneButton buttonReset(4, true); // Reset all leds button
OneButton buttonDisco(5, true); // Disco button

// On next led on the board
void upCount() {
  if(count < MAX_COUNT) {
     count++;
     digitalWrite(count, HIGH); 
  }
}

// Off prexious led on the board
void downCount() {
  if(count > MIN_COUNT - 1) {
    digitalWrite(count, LOW);
    leds[count] = LOW; 
    count--;
  }
}

// On next led on the board in flashing mode
void upDoubleCount() {
  if(count < MAX_COUNT) {
     count++;
     leds[count] = HIGH; 
  }
}

// Off all leds on the board
// Set button pointer on left position
void dropAllLeds() {
  count = 7;
  for(int i = 8; i < 14; i++) {
    leds[i] = LOW;
    digitalWrite(i, LOW);
  } 
}

// On all leds in disco mode (flashing mode)
void makeDisco() {
  count = 13;
  for(int i = 8; i < 14; i++) {
    leds[i] = HIGH;
    digitalWrite(i, LOW);
  }
}

void setup() {
  for(int i = 8; i < 14; i++) {
    leds[i] = LOW;
    pinMode(i, OUTPUT);
  }

  buttonLeft.setClickTicks(200);
  buttonRight.setClickTicks(200);
  buttonLeft.attachClick(downCount);
  buttonRight.attachClick(upCount);
  buttonLeft.attachDoubleClick(upDoubleCount);
  buttonReset.attachClick(dropAllLeds);
  buttonDisco.attachClick(makeDisco);
}

void loop() {
  if(millis()%10 == 0) {
    buttonLeft.tick();
    buttonRight.tick();
    buttonReset.tick();
    buttonDisco.tick();
  
    if(millis()%100 == 0) {
        for(int i = 8; i < 14; i++) {
          if(leds[i] == HIGH) {
            digitalWrite(i, currentAction); 
          }
      }
      
      currentAction = !currentAction;
    }
  }
}




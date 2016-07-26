// ModesKeys
// Chiyoung Kim

// Middle pin of 2-state switch to D2
// Output pin from button array to A0
// Ground to ground (duh)
// Power to 5V

#include <HID.h>
#include <Keyboard.h>
#include <stdlib.h>

const int numPins = 2;
const int inPin[numPins] = {2, A0};

double buttonState[numPins] = {0, 0};         // current state of the button
int lastButtonState = 0;     // previous state of the button
int lastSwitchState;

char ctrlKey = KEY_LEFT_CTRL;
char altKey = KEY_LEFT_ALT;

void setup()                    // run once, when the sketch starts
{
  // initialize the button pin as a input:
  for (int i = 0; i < numPins; ++i) {
    pinMode(inPin[i], INPUT); 
  }
  
  Keyboard.begin();
  Serial.begin(9600);           // set up Serial library at 9600 bps

  Serial.println("Hello world!");  // prints hello with ending line break

  lastSwitchState = digitalRead(inPin[0]);
}


void loop()                       // run over and over again
{
  // read the state switch input pin (buttonstate[0]) and button input pin (buttonstate[1]):
  for (int i = 1; i < numPins; ++i) {
    buttonState[i] = analogRead(inPin[i]);
    if (buttonState[i] < 200) {
      buttonState[i] = 0;
    }
    else if (buttonState[i] < 1000) {
      buttonState[i] = 1;
    }
    else {
      buttonState[i] = 2;
    }
  }
  buttonState[0] = digitalRead(inPin[0]);
  // compare the buttonState to its previous state
  if (buttonState[1] != lastButtonState && lastButtonState == 0 && buttonState[0] == lastSwitchState) {
    if (buttonState[0] == 1) {
      if (buttonState[1] == 2) {
        command1();
      }
      else if (buttonState[1] == 1) {
        command2();
      }
    }
    else if (buttonState[0] == 0) {
      if (buttonState[1] == 2) {
        command3();
      }
      else if (buttonState[1] == 1) {
        command4();
      }
    }
    Serial.println(buttonState[0]);
    Serial.println(buttonState[1]);
    Serial.println(lastButtonState);
    Serial.println(lastSwitchState);
    // Delay a little bit to avoid bouncing
    delay(100);
  }
  lastButtonState = buttonState[1];
  lastSwitchState = buttonState[0];
}

void command1() {
  Keyboard.press(altKey);
  Keyboard.write(KEY_TAB);
  Keyboard.releaseAll();
}

void command2() {
  Keyboard.press(ctrlKey);
  Keyboard.press(altKey);
  Keyboard.write(KEY_DELETE);
  Keyboard.releaseAll();
}

void command3() {
  Keyboard.write(KEY_CAPS_LOCK);
  Keyboard.releaseAll();
}

void command4() {
  Keyboard.write(KEY_UP_ARROW);
  Keyboard.releaseAll();
}

/* 
 * 
 * Dpad for Arduino TinyTetris 
 * 
 * Designed for https://github.com/AJRussell/Tiny-Tetris
 * 
 * Clumsy code by tobozo (c+) 2016
 * Apologies for coding horror
 * 
 */
 
#ifndef DPADCPP
#define DPADCPP

#include <Arduino.h>

#ifndef KEYPAD_PIN
#define KEYPAD_PIN  A0
#endif

// this is for analog 5x momentary buttons dpad
// as seen here http://fritzing.org/projects/arduino-5-buttons-keypad
// put your resistor calibration values here
const int dpad[5][2] = {
  {-2, -1}, //KEY_MIDDLE 0
  {660, 690}, //KEY_LEFT 1
  {430, 460}, //KEY_RIGHT 2
  {700, 730}, //KEY_DOWN 3
  {540, 570}  //KEY_ROTATE 4
};

static int dpadwarp[5] = { 0,0,0,0,0 };
static volatile int Debounce = 0;
static volatile bool processKey = true;
static volatile int currentPos;


class Dpad
{

  static const int DebounceMax = 10;
  
  public:

    static int getPos() {
      
      currentPos = getPosition(KEYPAD_PIN)*1;
      delay(100);
      
      for(int i=0;i<5;i++) {
        if(currentPos > dpad[i][0] && currentPos < dpad[i][1]) {
          return i;  
        }
      }
      return -1;
    }

    static boolean DoDebounce() {
      Debounce++;
      if(Debounce > DebounceMax) {
        return true;
      }
      return false;
    }

    static int setAccel(int acceleration, int offset) {
      if(processKey) {
        dpadwarp[currentPos] = millis();
      }
      if(millis() < dpadwarp[currentPos] + offset) {
        processKey = false;
      } else {
        processKey = true;
        acceleration = acceleration + 70;
        if (acceleration > offset) {
          acceleration = offset;
        }
      }
      return acceleration;
    }

  private:
  
    static int getPosition(int pin) {
      return analogRead(pin);
    }
};

#endif



 

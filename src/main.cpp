#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
//#include "WiFi.h"
#include <Wire.h>
#include <Button2.h>
#include "esp_adc_cal.h"

#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif

#define TFT_MOSI            19
#define TFT_SCLK            18
#define TFT_CS              5
#define TFT_DC              16
#define TFT_RST             23

#define TFT_BL          4  // Display backlight control pin
#define ADC_EN          14
#define ADC_PIN         34
#define BUTTON_1        35
#define BUTTON_2        0
#define MAGNET      27

#define PRESSED LOW
#define NOT_PRESSED HIGH

TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library

const unsigned long shortPress = 80;
const unsigned long  longPress = 400;

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

char buff[512];
int vref = 1100;
int btnCick = false;
int buttonState = 0; 

boolean startTimer = false;
String minutesValue = "00";
String hoursValue = "00";
unsigned long blinkTimerMillis = 0;
unsigned long timerCountDownMillis = 0;
unsigned long countDownMillis = 1000;

int period = 1000;
unsigned long time_now = 0;
unsigned long startMillis;

long buttonTimer = 0;
long longPressTime = 5;

boolean buttonActive = false;
boolean longPressActive = false;

typedef struct Buttons {
    const byte pin = 26;
    const int debounce = 10;
 
    unsigned long counter=0;
    bool prevState = NOT_PRESSED;
    bool currentState;
} Button;

Button button;

void timerLogic() {
  /*
     Starts timer count down with values entered by the user.
     The minute value counts down and increments the countDownMillis 
     until both are zero.
  */
  unsigned long currentMillis = millis();
  if (startTimer) {
    if (currentMillis - timerCountDownMillis > countDownMillis) {
      minutesValue = minutesValue.toInt() - 1;
      timerCountDownMillis = currentMillis;
      if (hoursValue.toInt() == 0) {
        hoursValue = "00";
      }
      if ((hoursValue == "00") && (minutesValue.toInt() < 0)) {
        minutesValue = "00";
        startTimer = false;
      }
      else if (minutesValue.toInt() < 0) {
        minutesValue = 59;
        hoursValue = hoursValue.toInt() - 1;
      }
    }
  }
}

void displayLogic() {

    
    if(millis() - startMillis >= period){
    startMillis = millis();     

    tft.fillScreen(TFT_PURPLE);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(15, 45);
    tft.setTextSize(8);
    tft.print(hoursValue);
    tft.print(":");
    tft.print(minutesValue);
    }
}

void handleShortPress() {
    if(startTimer == false){
    hoursValue = hoursValue.toInt() + 5;
    tft.fillScreen(TFT_PURPLE);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(15, 45);
    tft.setTextSize(10);
    tft.print(hoursValue);
    tft.print(":");
    tft.print(minutesValue);
    }
}
 
void handleLongPress() {
   startTimer = true;
}

void buttonLogic() {
       // check the button
    button.currentState = digitalRead(button.pin);
 
    // has it changed?
    if (button.currentState != button.prevState) {
        delay(button.debounce);
        // update status in case of bounce
        button.currentState = digitalRead(button.pin);
        if (button.currentState == PRESSED) {
            // a new press event occured
            // record when button went down
            button.counter = millis();
        }
 
        if (button.currentState == NOT_PRESSED) {
            // but no longer pressed, how long was it down?
            unsigned long currentMillis = millis();
            //if ((currentMillis - button.counter >= shortPress) && !(currentMillis - button.counter >= longPress)) {
            if ((currentMillis - button.counter >= shortPress) && !(currentMillis - button.counter >= longPress)) {
                // short press detected. 
                handleShortPress();
            }
            if ((currentMillis - button.counter >= longPress)) {
                // the long press was detected
                handleLongPress();
            }
        }
        // used to detect when state changes
        button.prevState = button.currentState;
    } 
}

void setup()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_PURPLE);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(15, 45);
    tft.setTextSize(10);
    tft.print(hoursValue);
    tft.print(":");
    tft.print(minutesValue);

    pinMode(button.pin, INPUT_PULLUP);
    pinMode(MAGNET, OUTPUT);
    digitalWrite(MAGNET,LOW);
}

void loop()
{
    buttonLogic();
    timerLogic();
    if (startTimer == false) {
        digitalWrite(MAGNET,LOW);
    } else {       
        digitalWrite(MAGNET,HIGH);
        displayLogic();
    }
}
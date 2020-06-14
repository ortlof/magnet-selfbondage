#include <FS.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <Button2.h>
#include "esp_adc_cal.h"
#include "index.html.h"  //Web page header file 

#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>          //https://github.com/esp8266/Arduino
#endif

//needed for library
#include <DNSServer.h>
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

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
#define MAGNET      27

#define PRESSED LOW
#define NOT_PRESSED HIGH

WebServer server(80);

String header;

TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library

const unsigned long shortPress = 80;
const unsigned long  longPress = 400;

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

boolean subbyscare = false;
boolean buttonActive = false;
boolean longPressActive = false;
boolean startup = true;
boolean wifimode = false;

const int led = 13;

typedef struct Buttons {
    const byte pin = 26;
    const int debounce = 10;
 
    unsigned long counter=0;
    bool prevState = NOT_PRESSED;
    bool currentState;
} Button;

Button button;

void timerLogic() {
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


void tftprint(){
    tft.fillScreen(TFT_PURPLE);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(15, 45);
    tft.setTextSize(8);
    tft.print(hoursValue);
    tft.print(":");
    tft.print(minutesValue);
    String adcValue = String(hoursValue)+(":")+String(minutesValue);
    server.send(200, "text/plane", adcValue);
}

void displayLogic() {
    if(subbyscare == false){
    if(millis() - startMillis >= period){
    startMillis = millis();     
    tft.fillScreen(TFT_PURPLE);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(15, 45);
    tft.setTextSize(7);
    tft.print(hoursValue);
    tft.print(":");
    tft.print(minutesValue);
    }
  }
}

void handleShortPress() {
    if(startTimer == false){
    hoursValue = hoursValue.toInt() + 5;
    tftprint();
    }
}
 
void handleLongPress() {
  if(startTimer == false){
    startTimer = true;
  } else {
      startTimer = false;
    }
    
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

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handletime1() {
    hoursValue = hoursValue.toInt() + 10;
    tftprint();
}

void handletime2() {
    hoursValue = hoursValue.toInt() + 5;
    tftprint();
}

void handletime3() {
    startTimer = true;
}

void handletime4() {
    startTimer = false;
    minutesValue = "00";
    hoursValue = "00";
    tftprint();
}

void handletime5() {
    subbyscare = true;
}

void readadc(){
    String adcValue = String(hoursValue)+(":")+String(minutesValue);
    server.send(200, "text/plane", adcValue);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void handlewifistartup(){
      WiFiManager wifiManager;
      wifiManager.setTimeout(180);

      if(wifiManager.autoConnect()) {
        WiFi.setHostname("lockmeup");
        tft.setTextSize(2);
        tft.setCursor(30, 45);
        tft.print("IP-Adress:");
        tft.setCursor(10, 75);
        tft.print(WiFi.localIP());
        wifimode = true;
      } else {
        wifiManager.startConfigPortal("OnDemandAP");
        WiFi.setHostname("lockmeup");
        tft.setTextSize(2);
        tft.setCursor(30, 45);
        tft.print("Wifi Mode");
        tft.setCursor(10, 75);
        tft.print(WiFi.localIP());
        wifimode = true;
      }
    
}

void setup(){
    Serial.begin(115200);
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_PURPLE);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(50, 10);
    tft.setTextSize(3);
    tft.print("LockMeUP");
    
    pinMode(button.pin, INPUT_PULLUP);
    pinMode(MAGNET, OUTPUT);
    digitalWrite(MAGNET,LOW);

    button.currentState = digitalRead(button.pin);
    if(button.currentState == LOW){
      handlewifistartup();
    }

    if (wifimode == true){
    server.on("/", handleRoot);
    server.on("/readADC", readadc);
    server.on("/time1", handletime1);
    server.on("/time2", handletime2);
    server.on("/time3", handletime3);
    server.on("/time4", handletime4);
    server.on("/time5", handletime5);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
    }

  }

void loop(){
  if (wifimode == true){
    WiFiClient client;
    const int httpPort = 80;
    server.handleClient();
  }
    buttonLogic();
    timerLogic();
    if (startTimer == false) {
        digitalWrite(MAGNET,LOW);
    } else {       
        digitalWrite(MAGNET,HIGH);
        displayLogic();
    }
}
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>
#include <Fonts/FreeSerif24pt7b.h>  // Larger font for the first line
#include <Fonts/FreeSerif18pt7b.h>  // Smaller font for the second and third lines

MCUFRIEND_kbv tft;
SoftwareSerial bluetooth(10, 11); // RX, TX

#define BLACK   0x0000
#define WHITE   0xFFFF

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320

String firstLine = "Waiting for Bluetooth data...";
String secondLine = "";
String thirdLine = "";

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1); // Landscape orientation for 480x320
  tft.fillScreen(WHITE);
  
  tft.setTextColor(BLACK);
  
  displayCenteredTexts();
}

void loop() {
  if (bluetooth.available()) {
    String newInput = "";
    while (bluetooth.available()) {
      char c = bluetooth.read();
      newInput += c;
      delay(10);
    }
    
    if (firstLine == "Waiting for Bluetooth data...") {
      firstLine = newInput;
    } else if (secondLine.length() == 0) {
      secondLine = newInput;
    } else if (thirdLine.length() == 0) {
      thirdLine = newInput;
    } else {
      // If all lines are filled, shift them up
      firstLine = secondLine;
      secondLine = thirdLine;
      thirdLine = newInput;
    }
    
    displayCenteredTexts();
  }
}

void displayCenteredTexts() {
  tft.fillScreen(WHITE); // Clear the screen
  
  int16_t x1, y1;
  uint16_t w1, h1, w2, h2, w3, h3;
  
  // Set larger font for the first line
  tft.setFont(&FreeSerif24pt7b);
  
  // Get bounds of first text
  tft.getTextBounds(firstLine, 0, 0, &x1, &y1, &w1, &h1);
  
  // Calculate position for first text
  int x1_pos = (DISPLAY_WIDTH - w1) / 2;
  int y1_pos = DISPLAY_HEIGHT / 4; // Position at 1/4 of the screen height
  
  // Display first text
  tft.setCursor(x1_pos, y1_pos);
  tft.println(firstLine);
  
  // Set smaller font for the second and third lines
  tft.setFont(&FreeSerif18pt7b);
  
  // Display second text
  if (secondLine.length() > 0) {
    tft.getTextBounds(secondLine, 0, 0, &x1, &y1, &w2, &h2);
    int x2_pos = (DISPLAY_WIDTH - w2) / 2;
    int y2_pos = y1_pos + h1 + 15; // Add some space between lines
    
    tft.setCursor(x2_pos, y2_pos);
    tft.println(secondLine);
  }
  
  // Display third text
  if (thirdLine.length() > 0) {
    tft.getTextBounds(thirdLine, 0, 0, &x1, &y1, &w3, &h3);
    int x3_pos = (DISPLAY_WIDTH - w3) / 2;
    int y3_pos = y1_pos + h1 + h2 + 30; // Add more space for the third line
    
    tft.setCursor(x3_pos, y3_pos);
    tft.println(thirdLine);
  }
}
#include <FastLED.h>

#define Letter_width = 5
#define LED_PIN 7    
#define NUM_LEDS 25 
#define NUM_ROWS 5  
#define NUM_COLS 5
#define LETTER_SIZE 5  

CRGB leds[NUM_LEDS];
bool RANDOMCOLOR = true;
CRGB COLOR = CRGB::Aqua;
int RED = 0;
int GREEN = 00;
int BLUE = 255;

int space = 6;  //put 6 if you want a bit between letters, 5 if you want them side by side, 4 and itll there will be cross talk.
int Brightness = 100;
int speed = 30;  // higher number is slower
char message[] = "Test Message";
//char message[] = "zz pearl";

int messPart = 0;
int temp[5];
byte fullmes[1000];
byte lilBit[5];
byte firstletter[5];
bool FirstLetter = true;
bool RUP = true;
bool GUP = true;
bool BUP = true;
int count = 0;

int letters[][5] = {
  { B00000, B00000, B00000, B00000, B00000 },  //
  { B00100, B01010, B10001, B11111, B10001 },  // A
  { B11110, B10001, B11110, B10001, B01110 },  // B
  { B01110, B10001, B10000, B10001, B01110 },  // C
  { B11110, B10001, B10001, B10001, B01110 },  // D
  { B01111, B01000, B01110, B01000, B01111 },  // E
  { B11110, B10000, B11100, B10000, B10000 },  // F
  { B01110, B10001, B10000, B10110, B01110 },  // G
  { B10001, B10001, B11111, B10001, B10001 },  // H
  { B11111, B00100, B00100, B00100, B11111 },  // I
  { B00111, B00001, B00001, B10001, B01110 },  // J
  { B10001, B10010, B11100, B10010, B10001 },  // K
  { B10000, B10000, B10000, B10000, B11110 },  // L
  { B10001, B11011, B10101, B10001, B10001 },  // M
  { B10001, B11001, B10101, B10011, B10001 },  // N
  { B01110, B10001, B10001, B10001, B01110 },  // O
  { B11110, B10001, B11110, B10000, B10000 },  // P
  { B01110, B10001, B10101, B10010, B01101 },  // Q
  { B11110, B10001, B11110, B10010, B10001 },  // R
  { B01111, B10000, B01110, B00001, B11110 },  // S
  { B11111, B00100, B00100, B00100, B00100 },  // T
  { B10001, B10001, B10001, B10001, B01110 },  // U
  { B10001, B10001, B01010, B01010, B00100 },  // V
  { B10001, B10001, B10101, B11011, B10001 },  // W
  { B10001, B01010, B00100, B01010, B10001 },  // X
  { B10001, B01010, B00100, B00100, B00100 },  // Y
  { B01010, B10101, B10001, B01010, B00100 }   // Z = heart for this pattern
  //{ B11111, B00010, B00100, B01000, B11111 }   // Z
};
/*
int letters[][5] = {
  { B00000, B00000, B00000, B00000, B00000 },  //
  { B01100, B10010, B10010, B11110, B10010 },  // A
  { B11100, B10010, B11100, B10010, B11100 },  // B
  { B01100, B10010, B10000, B10010, B01100 },  // C
  { B11100, B10010, B10010, B10010, B11100 },  // D
  { B01111, B01000, B01110, B01000, B01111 },  // E
  { B11110, B10000, B11100, B10000, B10000 },  // F
  { B01100, B10010, B10000, B10010, B01110 },  // G
  { B10010, B10010, B11110, B10010, B10010 },  // H
  { B11100, B01000, B01000, B01000, B11100 },  // I
  { B00110, B00010, B00010, B10010, B01100 },  // J
  { B10010, B10100, B11000, B10100, B10010 },  // K
  { B10000, B10000, B10000, B10000, B11110 },  // L
  { B10001, B11011, B10101, B10001, B10001 },  // M
  { B10010, B11010, B10110, B10010, B10010 },  // N
  { B01100, B10010, B10010, B10010, B01100 },  // O
  { B11100, B10010, B11100, B10000, B10000 },  // P
  { B01110, B10001, B10101, B10010, B01101 },  // Q
  { B1110, B1001, B1110, B1010, B1001 },  // R
  { B01110, B10000, B01100, B00010, B11100 },  // S
  { B11111, B00100, B00100, B00100, B00100 },  // T
  { B10010, B10010, B10010, B10010, B01100 },  // U
  { B10001, B10001, B01010, B01010, B00100 },  // V
  { B10001, B10001, B10101, B11011, B10001 },  // W
  { B10001, B01010, B00100, B01010, B10001 },  // X
  { B10001, B01010, B00100, B00100, B00100 },  // Y
  { B01010, B10101, B10001, B01010, B00100 }   // Z = heart for this pattern
  //{ B01111, B00010, B00100, B01000, B01111 }   // Z
};
*/

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);  
  FastLED.setBrightness(Brightness);                      
  fill_solid(leds, NUM_LEDS, CRGB::Black);                
  FastLED.show();
  fullMessage();
}

void loop() {
  getPeice();
  for (int i = 0; i < space; i++) {
    getByte();
    displayLetter(lilBit);
    delay(speed*10);
  }
}

void getPeice() {
  if (messPart >= strlen(message)) {
    messPart = 0;
    FirstLetter = true;
  }
  if (messPart == 0 && FirstLetter) {
    for (int i = 0; i < NUM_ROWS; i++) {
      temp[i] = 0 << space | (letters[fullmes[messPart]][i]);
      FirstLetter = false;
    }
  } else if (messPart < strlen(message)) {
    for (int i = 0; i < NUM_ROWS; i++) {
      temp[i] = (letters[fullmes[messPart]][i]) << space | (letters[fullmes[messPart + 1]][i]);
    }
    messPart++;
  } else {
    messPart++;
    for (int i = 0; i < NUM_ROWS; i++) {
      temp[i] = 0;
    }
  }
}

void fullMessage() {
  int letterCount = 0;
  for (int i = 0; i < strlen(message); i++) {
    char currentChar = toupper(message[i]);  // Convert to uppercase
    if (currentChar >= 'A' && currentChar <= 'Z') {
      int letterIndex = currentChar - 'A' + 1;  // Map A to 0, B to 1, etc.
      fullmes[i] = letterIndex;
      letterCount++;
      delay(50);
    }
  }
}

void colorChange()
{
  if (RED<=254 && RUP) RED++;
  else if (BLUE <= 254 && BUP) BLUE++;
  else if (GREEN <= 254 && GUP) GREEN++;

  if (RED == 255) RUP = false;
  if (BLUE == 255) BUP = false;
  if (GREEN == 255) GUP = false;

  if (BLUE >= 1 && !BUP) BLUE--;
  else if (RED>=11 && !RUP) RED--;
  else if (GREEN >= 1 && !GUP) GREEN--;

  if (RED == 10) {
  RUP = true;
  BUP = true;
  GUP = true;
  }
  COLOR = CRGB(RED,GREEN,BLUE);
}

void displayLetter(byte pattern[5]) {
  if (RANDOMCOLOR) colorChange();
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      int index;
      if (i % 2 == 0) {
        index = i * LETTER_SIZE + j;  //To the right
      } else {
        index = i * LETTER_SIZE + (4 - j);  //To the left
      }
      
      if (bitRead(pattern[i], j) == 1) {
        leds[index] = COLOR;            // Change this to change the color
      } else {
        leds[index] = CRGB::Black;
      }
    }
  }
  FastLED.show();
}

void getByte() {
  if (count == space) count = 0;
  for (int i = 0; i < NUM_ROWS; i++) {
    lilBit[i] = (temp[i] >> (space - count) & 0x1F);
  }
  count++;
}



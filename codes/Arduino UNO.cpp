#include "RTClib.h"

#define A 13
#define B A1
#define C A2
#define D A3
#define sevenSegmentDP 3
#define dataPin 2
#define clockPin 4
#define latchPin 7
#define speakerPin 8
#define NodeMCU_PIN 9

RTC_DS1307 rtc;
DateTime now;

byte displayPins[6] = {A0, 5, 6, 12, 10, 11};
byte second;
byte minute;
byte hour;
byte day;
byte month;
int year;
unsigned long t;
byte countDisplay;
unsigned long t2;
String mode = "clock";
unsigned long t3;
byte zero[8] = {0b00111100, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b00111100};
byte intensity7seg;
byte lastSecond;
unsigned long t4;
byte soundIndex;
unsigned long t5;
String received;
String command;
byte soundMode;
unsigned long t6;
boolean NMCU0_ENABLE;
unsigned long t7;
boolean noteDirection;
byte noteIndex;
unsigned long t8;
boolean LED_DIRECTION;
byte LED_INDEX;
byte clockLEDs;

const unsigned int notes[7] = {1760, 1976, 2093, 2349, 2637, 2794, 3136};

const byte soundArraySize = 100;

unsigned int T[soundArraySize];

unsigned int F[soundArraySize];

byte digits[10][8] = {
  {0b00111100, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b00111100},// 0
  {0b00011000, 0b00111000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00111100},// 1
  {0b00000000, 0b00011000, 0b00100100, 0b00000100, 0b00001000, 0b00010000, 0b00111100, 0b00000000},// 2
  {0b00000000, 0b00111100, 0b00000100, 0b00000100, 0b00111100, 0b00000100, 0b00000100, 0b00111100},// 3
  {0b00000000, 0b00100100, 0b00100100, 0b00100100, 0b00111100, 0b00000100, 0b00000100, 0b00000100},// 4
  {0b00111100, 0b00100000, 0b00100000, 0b00111000, 0b00000100, 0b00000100, 0b00100100, 0b00011000},// 5
  {0b00011000, 0b00100100, 0b00100000, 0b00111000, 0b00100100, 0b00100100, 0b00100100, 0b00011000},// 6
  {0b00111100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100},// 7
  {0b00000000, 0b00011000, 0b00100100, 0b00100100, 0b00011000, 0b00100100, 0b00100100, 0b00011000},// 8
  {0b00011000, 0b00100100, 0b00100100, 0b00011100, 0b00000100, 0b00000100, 0b00100100, 0b00011000}// 9
};

byte Year[20][8] = {
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
  {0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00011100, 0b00100100, 0b00100100, 0b00011000},// ძ
  {0b00011000, 0b00100100, 0b00000100, 0b00011000, 0b00000100, 0b00000100, 0b00100100, 0b00011000},// ვ
  {0b00011000, 0b00100100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00100100, 0b00011000},// ე
  {0b00011000, 0b00100100, 0b00100000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000100},// ლ
  {0b00111100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00100100},// ი
  {0b00000000, 0b01111110, 0b10001001, 0b10001001, 0b10001001, 0b10001001, 0b01110010, 0b00000000},// თ
  {0b00000000, 0b00011000, 0b00100100, 0b00000100, 0b00001000, 0b00010000, 0b00111100, 0b00000000},// 2
  {0b00000000, 0b00111100, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b00111100, 0b00000000},// 0
  {0b00000000, 0b00011000, 0b00100100, 0b00000100, 0b00001000, 0b00010000, 0b00111100, 0b00000000},// 2
  {0b00000000, 0b00111100, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b00111100, 0b00000000},// 0
  {0b00000000, 0b00000000, 0b00000000, 0b01111110, 0b01111110, 0b00000000, 0b00000000, 0b00000000},// -
  {0b00000000, 0b00111100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00111100, 0b00000000},// O
  {0b00000000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00111100, 0b00000000},// L
  {0b00000000, 0b00110000, 0b00101000, 0b00100100, 0b00100100, 0b00101000, 0b00110000, 0b00000000},// D
  {0b00000000, 0b00011000, 0b00100100, 0b00000100, 0b00001000, 0b00010000, 0b00111100, 0b00000000},// 2
  {0b00000000, 0b00111100, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b00111100, 0b00000000},// 0
  {0b00000000, 0b00011000, 0b00100100, 0b00000100, 0b00001000, 0b00010000, 0b00111100, 0b00000000},// 2
  {0b00000000, 0b00111100, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b00111100, 0b00000000},// 0
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}
};

void RTC()  {
  now = rtc.now();
  second = now.second();
  minute = now.minute();
  hour = now.hour();
  day = now.day();
  month = now.month();
  year = now.year();
}

void disable7segments() {
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
}

void displayDigits(byte digit, boolean DP, byte displayIndex, boolean displayEnable)  {
  digitalWrite(sevenSegmentDP, !DP);
  if (displayEnable) {
    digitalWrite(A, digit & (1 << 0));
    digitalWrite(B, digit & (1 << 1));
    digitalWrite(C, digit & (1 << 2));
    digitalWrite(D, digit & (1 << 3));
  }
  else  {
    disable7segments();
  }
  digitalWrite(displayPins[displayIndex], 1);
}

void multiplexSegments()  {// 7-სეგმენტა ინდიკატორებზე დროის გამოსახვის ფუნქცია
  if (countDisplay == 0)  {
    digitalWrite(displayPins[5], 0);
    displayDigits(hour / 10, 0, 0, 1);
  }
  else if (countDisplay == 1) {
    digitalWrite(displayPins[0], 0);
    displayDigits(hour % 10, 1, 1, 1);
  }
  else if (countDisplay == 2) {
    digitalWrite(displayPins[1], 0);
    displayDigits(minute / 10, 0, 2, 1);
  }
  else if (countDisplay == 3) {
    digitalWrite(displayPins[2], 0);
    displayDigits(minute % 10, 1, 3, 1);
  }
  else if (countDisplay == 4) {
    digitalWrite(displayPins[3], 0);
    displayDigits(second / 10, 0, 4, 1);
  }
  else if (countDisplay == 5) {
    digitalWrite(displayPins[4], 0);
    displayDigits(second % 10, 0, 5, 1);
  }
}

void shiftMatrix(byte rows, byte columns, boolean bitOrder_row, boolean bitOrder_column)  {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, bitOrder_row, rows);
  shiftOut(dataPin, clockPin, bitOrder_column, columns);
  digitalWrite(latchPin, 1);
}

void matrixFull(boolean state) {
  shiftMatrix(map(state, 0, 1, 0, 0xFF), 0, LSBFIRST, LSBFIRST);
}

void matrixLED(byte row, byte column)  {
  shiftMatrix(1 << row, 0xFF ^ (1 << column), LSBFIRST, LSBFIRST);
}

void matrixRow(byte row, byte number)  {
  shiftMatrix(1 << row, 0xFF ^ number, LSBFIRST, MSBFIRST);
}

void matrixColumn(byte column, byte number)  {
  shiftMatrix(number, 0xFF ^ (1 << column), LSBFIRST, MSBFIRST);
}

void matrixDigit(byte digit) {
  for (byte i = 0; i < 8; i++)
    matrixRow(i, digits[digit][i]);
}

void scrollYear(byte charIndex) {
  for (byte scroll = 1; scroll <= 8; scroll++)  {
    for (t3 = millis(); (millis() - t3) < 75; forFunction()) {
      for (byte i = 0; i < 8; i++)
        matrixRow(i, (Year[charIndex][i] << scroll) | (Year[charIndex + 1][i] >> (8 - scroll)));
    }
  }
}

void sound2020()  {
  if (millis() - t4 >= T[soundIndex])  {
    tone(speakerPin, F[soundIndex]);
    if (++soundIndex == soundArraySize) {
      soundIndex = 0;
      soundInitialize();
    }
    t4 = millis();
  }
}

void sevenSegments()  {
  multiplexSegments();
  if (++countDisplay == 6)
    countDisplay = 0;
}

void forFunction()  {
  clockFunction();
  function2020();
}

void soundInitialize()  {
  randomSeed(now.unixtime());
  for (byte a = 0; a < soundArraySize; a++) {
    T[a] = random(100, 250);
    F[a] = random(250, 5000);
  }
}

void servo(byte angle)  {
  command = "SRV" + String("|") + String(angle);
  Serial.print(command);
}

void LED(boolean state)  {
  command = "LED" + String("|") + String(state);
  Serial.print(command);
}

void buzzer(char m, unsigned int val) {
  command = "BZR" + String("|") + String(m) + String("|") + String(val);
  Serial.print(command);
}

void counter(String m, byte val)  {
  command = "CNT" + String("|") + String(m) + String("|") + String(val);
  Serial.print(command);
}

void RGB(byte red, byte green, byte blue)  {
  command = "RGB" + String("|") + String(red) + String("|") + String(green) + String("|") + String(blue);
  Serial.print(command);
}

void TRGB(unsigned int T) {
  command = "TRGB" + String("|") + String(T);
  Serial.print(command);
}

void RGB2(byte intensity, boolean red, boolean green, boolean blue) {
  command = "RGB2" + String("|") + String(intensity) + String("|") + String(red) + String("|") + String(green) + String("|") + String(blue);
  Serial.print(command);
}

void TRGB2(unsigned int T) {
  command = "TRGB2" + String("|") + String(T);
  Serial.print(command);
}

void LEDs(char colour, boolean state)  {
  command = "LED" + String(colour) + String("|") + String(state);
  Serial.print(command);
}

void NMCU(boolean state) {
  if (state)  {
    digitalWrite(NodeMCU_PIN, 1);
    NMCU0_ENABLE = 1;
    t6 = millis();
  }
  else if ((millis() - t6 >= 1250) && NMCU0_ENABLE)  {
    digitalWrite(NodeMCU_PIN, 0);
    NMCU0_ENABLE = 0;
  }
}

void delayFunction(byte delayTime)  {
  for (t8 = millis(); millis() - t8 < delayTime; multiplexSegments());
}

void clockFunction()  {
  NMCU(0);
  if (millis() - t5 >= 500)  {
    rtc.writeSqwPinMode(DS1307_OFF);
  }
  if (millis() - t2 >= 1)  {
    sevenSegments();
    t2 = millis();
  }
  if (millis() - t >= 1000)  {
    rtc.writeSqwPinMode(DS1307_ON);
    t5 = millis();
    RTC();
    if (month == 1 && day == 13 && hour == 23 && minute == 57 && second == 59)  {
      LED(1);
    }
    else if (month == 1 && day == 13 && hour == 23 && minute == 58 && second == 0) {
      servo(180);
    }
    if (month == 1 && day == 13 && hour == 23 && minute == 59 && second == 50)  {
      mode = "countDown";
    }
    else if (month == 1 && day == 14 && hour == 0 && minute == 0 && second == 0) {
      mode = "newYear";
      servo(0);
    }
    else if (mode == "clock") {
      clock();
    }
    t = millis();
  }
}

void sound2020_2(byte soundTime)  {
  if (millis() - t4 >= soundTime)  {
    tone(speakerPin, F[soundIndex]);
    if (++soundIndex == soundArraySize) {
      soundIndex = 0;
      soundInitialize();
    }
    t4 = millis();
  }
}

void counterLEDs()  {
  counter("LED", LED_INDEX);
  if (LED_INDEX == 0)
    LED_DIRECTION = 1;
  else if (LED_INDEX == 9)
    LED_DIRECTION = 0;
  if (LED_DIRECTION)
    LED_INDEX++;
  else
    LED_INDEX--;
}

void notesSound(unsigned int noteTime) {
  if (millis() - t7 >= noteTime)  {
    counterLEDs();
    tone(speakerPin, notes[noteIndex]);
    if (noteIndex == 0)
      noteDirection = 1;
    else if (noteIndex == 6)
      noteDirection = 0;
    if (noteDirection)
      noteIndex++;
    else
      noteIndex--;
    t7 = millis();
  }
}

void soundFunction()  {
  if (soundMode == 0)  {
    sound2020();
  }
  else if (soundMode == 1) {
    sound2020_2(100);
  }
  else if (soundMode == 2) {
    sound2020_2(500);
  }
  else if (soundMode == 3) {
    notesSound(250);
  }
}

void function2020() {
  NMCU(0);
  if (!(month == 1 && day == 14 && hour == 0 && minute == 0 && second == 0) && !(month == 1 && day == 14 && hour == 0 && minute == 0 && second == 1) && !(month == 1 && day == 14 && hour == 0 && minute == 0 && second == 2) && !(month == 1 && day == 14 && hour == 0 && minute == 0 && second == 3))
    soundFunction();
  if (month == 1 && day == 14 && hour == 0 && minute == 0 && second == 1)  {
    tone(speakerPin, 3000);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 0 && second == 2)  {
    tone(speakerPin, 2000);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 0 && second == 3)  {
    tone(speakerPin, 1000);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 0 && second == 4) {
    noTone(speakerPin);
    NMCU(1);
    TRGB(1);
    delayFunction(30);
    TRGB2(1);
    delayFunction(30);
    counter("LED", 8);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 0 && second == 30) {
    NMCU(1);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 0 && second == 45) {
    NMCU(1);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 1 && second == 0) {
    NMCU(1);
    soundMode = 1;
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 1 && second == 15) {
    NMCU(1);
    soundMode = 2;
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 1 && second == 30) {
    NMCU(1);
    soundMode = 3;
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 1 && second == 35) {
    NMCU(1);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 1 && second == 45) {
    NMCU(1);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 1 && second == 55) {
    NMCU(1);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 2 && second == 10) {
    NMCU(1);
    soundMode = 4;
    tone(speakerPin, 1500);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 2 && second == 11) {
    tone(speakerPin, 2500);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 2 && second == 12) {
    tone(speakerPin, 3500);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 2 && second == 13) {
    noTone(speakerPin);
    buzzer('D', 1);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 2 && second == 14) {
    buzzer('D', 0);
  }
  else if (month == 1 && day == 14 && hour == 0 && minute == 2 && second == 15) {
    NMCU(1);
  }
}

void clock()  {
  matrixLED((now.unixtime() % 64) / 8, now.unixtime() % 8);
  if (clockLEDs == 0)  {
    LEDs('b', 0);
    delayFunction(30);
    LEDs('r', 1);
    clockLEDs = 1;
  }
  else if (clockLEDs == 1)  {
    LEDs('r', 0);
    delayFunction(30);
    LEDs('g', 1);
    clockLEDs = 2;
  }
  else if (clockLEDs == 2) {
    LEDs('g', 0);
    delayFunction(30);
    LEDs('b', 1);
    clockLEDs = 0;
  }
}

void countDown()  {
  if (second != lastSecond) {
    tone(speakerPin, 2500, 100);
  }
  lastSecond = second;
  matrixDigit(9 - (second % 10));
}

void newYear()  {
  if (month == 1 && day == 14 && hour == 0 && minute == 0 && second == 0)  {
    for (byte j = 0; j < 8; zero[j++] = 0) {
      for (t3 = millis(); (millis() - t3) < 50; forFunction()) {
        for (byte i = 0; i < 8; i++)  {
          matrixRow(i, zero[i]);
        }
      }
    }
  }
  for (byte i = 0; i < 19; i++)
    scrollYear(i);
  clockFunction();
}

void setup()  {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(sevenSegmentDP, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(NodeMCU_PIN, OUTPUT);
  for (byte i = 0; i < 6; i++)
    pinMode(displayPins[i], OUTPUT);
  rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2020, 1, 13, 23, 57, 0));
  //rtc.writeSqwPinMode(DS1307_SquareWave1HZ);
  RTC();
  matrixFull(0);
  soundInitialize();
  Serial.begin(57600);
  Serial.setTimeout(25);
}

void loop() {
  if (Serial.available())  {
    received = Serial.readString();
    if (received == "time+")  {
      rtc.adjust(DateTime(now.unixtime() + 1));
      RTC();
    }
    else if (received == "time-") {
      rtc.adjust(DateTime(now.unixtime() - 1));
      RTC();
    }
  }
  clockFunction();
  if (mode == "countDown")
    countDown();
  else if (mode == "newYear")
    newYear();
}

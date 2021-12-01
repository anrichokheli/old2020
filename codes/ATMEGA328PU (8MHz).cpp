#include <Servo.h>

#define PB1 2
#define PB2 12
#define servoPin 4
#define LED_PIN 7
#define buzzerPin 8
#define clockPin 13
#define resetPin A0
#define counterVcc A1
#define redPin 11
#define greenPin 5
#define bluePin 6
#define RGB_GND 3
#define RGB_RED 9
#define RGB_GREEN 10
#define RGB_BLUE A2
#define LEDr A3
#define LEDg A4
#define LEDb A5

volatile unsigned long t;

Servo servo;

String received;
String mode;
boolean counterAllLED;
boolean RGBcoloursEnable;
byte redValue;
byte greenValue;
byte blueValue;
byte colourMode;
unsigned long t2;
unsigned int RGB_TIME;
boolean RGB2coloursEnable;
unsigned long t3;
unsigned int RGB2_TIME;
byte RGBvalue;
boolean redState;
boolean greenState;
boolean blueState;
byte colourMode2;

String getText(String text, char symbol, byte index)  {
  byte charIndex[text.length()];
  byte I = 0;
  for (byte i = 0; i < text.length(); i++)
    if (text.charAt(i) == symbol)
      charIndex[I++] = i;
  if (!index)
    return text.substring(index, text.indexOf(symbol));
  else if (text.indexOf(symbol, charIndex[index - 1] + 1) != -1)
    return text.substring(charIndex[index - 1] + 1, charIndex[index]);
  else
    return text.substring(charIndex[index - 1] + 1);
}

void counterInitialize()  {
  digitalWrite(clockPin, 0);
  digitalWrite(counterVcc, 1);
  digitalWrite(resetPin, 1);
  digitalWrite(resetPin, 0);
}

void counterLED(byte n) {
  counterInitialize();
  for (byte i = 0; i < n; i++) {
    digitalWrite(clockPin, 1);
    digitalWrite(clockPin, 0);
  }
}

void RGB(byte red, byte green, byte blue)  {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void RGB2(byte intensity, boolean red, boolean green, boolean blue) {
  analogWrite(RGB_GND, 255 - intensity);
  digitalWrite(RGB_RED, red);
  digitalWrite(RGB_GREEN, green);
  digitalWrite(RGB_BLUE, blue);
}

void RGBcolours() {
  if (redValue < 255 && colourMode == 0)  {
    if (++redValue == 255)
      colourMode = 1;
  }
  else if (greenValue < 255 && colourMode == 1)  {
    if (++greenValue == 255)
      colourMode = 2;
  }
  else if (redValue > 0 && colourMode == 2)  {
    if (--redValue == 0)
      colourMode = 3;
  }
  else if (blueValue < 255 && colourMode == 3)  {
    if (++blueValue == 255)
      colourMode = 4;
  }
  else if (greenValue > 0 && colourMode == 4)  {
    if (--greenValue == 0)
      colourMode = 5;
  }
  else if (redValue < 255 && colourMode == 5)  {
    if (++redValue == 255)
      colourMode = 6;
  }
  else if (greenValue < 255 && colourMode == 6)  {
    if (++greenValue == 255)
      colourMode = 7;
  }
  else if (greenValue > 0 && colourMode == 7)  {
    if (--greenValue == 0)
      colourMode = 8;
  }
  else if (redValue > 0 && colourMode == 8)  {
    if (--redValue == 0)
      colourMode = 9;
  }
  else if (greenValue < 255 && colourMode == 9)  {
    if (++greenValue == 255)
      colourMode = 10;
  }
  else if (blueValue > 0 && colourMode == 10)  {
    if (--blueValue == 0)
      colourMode = 11;
  }
  else if (redValue < 255 && colourMode == 11)  {
    if (++redValue == 255)
      colourMode = 12;
  }
  else if (greenValue > 0 && colourMode == 12)  {
    if (--greenValue == 0)
      colourMode = 13;
  }
  else if (redValue > 0 && colourMode == 13)  {
    if (--redValue == 0)
      colourMode = 0;
  }
}

void RGB2colours()  {
  if (colourMode2 == 0)  {
    redState = 1;
    greenState = 0;
    blueState = 0;
    colourMode2 = 1;
  }
  else if (colourMode2 == 1 && RGBvalue < 255) {
    if (++RGBvalue == 255)
      colourMode2 = 2;
  }
  else if (colourMode2 == 2 && RGBvalue > 0) {
    if (--RGBvalue == 0)
      colourMode2 = 3;
  }
  else if (colourMode2 == 3) {
    greenState = 1;
    colourMode2 = 4;
  }
  else if (colourMode2 == 4 && RGBvalue < 255) {
    if (++RGBvalue == 255)
      colourMode2 = 5;
  }
  else if (colourMode2 == 5 && RGBvalue > 0) {
    if (--RGBvalue == 0)
      colourMode2 = 6;
  }
  else if (colourMode2 == 6) {
    redState = 0;
    colourMode2 = 7;
  }
  else if (colourMode2 == 7 && RGBvalue < 255) {
    if (++RGBvalue == 255)
      colourMode2 = 8;
  }
  else if (colourMode2 == 8 && RGBvalue > 0) {
    if (--RGBvalue == 0)
      colourMode2 = 9;
  }
  else if (colourMode2 == 9) {
    blueState = 1;
    colourMode2 = 10;
  }
  else if (colourMode2 == 10 && RGBvalue < 255) {
    if (++RGBvalue == 255)
      colourMode2 = 11;
  }
  else if (colourMode2 == 11 && RGBvalue > 0) {
    if (--RGBvalue == 0)
      colourMode2 = 12;
  }
  else if (colourMode2 == 12) {
    greenState = 0;
    colourMode2 = 13;
  }
  else if (colourMode2 == 13 && RGBvalue < 255) {
    if (++RGBvalue == 255)
      colourMode2 = 14;
  }
  else if (colourMode2 == 14 && RGBvalue > 0) {
    if (--RGBvalue == 0)
      colourMode2 = 15;
  }
  else if (colourMode2 == 15) {
    redState = 1;
    colourMode2 = 16;
  }
  else if (colourMode2 == 16 && RGBvalue < 255) {
    if (++RGBvalue == 255)
      colourMode2 = 17;
  }
  else if (colourMode2 == 17 && RGBvalue > 0) {
    if (--RGBvalue == 0)
      colourMode2 = 18;
  }
  else if (colourMode2 == 18) {
    greenState = 1;
    colourMode2 = 19;
  }
  else if (colourMode2 == 19 && RGBvalue < 255) {
    if (++RGBvalue == 255)
      colourMode2 = 20;
  }
  else if (colourMode2 == 20 && RGBvalue > 0) {
    if (--RGBvalue == 0)
      colourMode2 = 0;
  }
}

void EXTERNAL_ISR()  {
  if (millis() - t > 250)  {
    if (digitalRead(PB2))
      Serial.print("time-");
    else
      Serial.print("time+");
    t = millis();
  }
}

void setup()  {
  pinMode(LED_PIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(counterVcc, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(RGB_GND, OUTPUT);
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  pinMode(LEDr, OUTPUT);
  pinMode(LEDg, OUTPUT);
  pinMode(LEDb, OUTPUT);
  pinMode(PB2, INPUT);
  Serial.begin(57600);
  Serial.setTimeout(25);
  attachInterrupt(digitalPinToInterrupt(PB1), EXTERNAL_ISR, RISING);
  servo.attach(servoPin);
  servo.write(0);
}

void loop() {
  if (Serial.available())  {
    received = Serial.readString();
    mode = getText(received, '|', 0);
    if (mode == "SRV")  {
      servo.write(getText(received, '|', 1).toInt() % 181);
    }
    else if (mode == "LED") {
      digitalWrite(LED_PIN, getText(received, '|', 1).toInt());
    }
    else if (mode == "BZR") {
      noTone(buzzerPin);
      digitalWrite(buzzerPin, 0);
      if (getText(received, '|', 1) == "D")
        digitalWrite(buzzerPin, getText(received, '|', 2).toInt());
      else if (getText(received, '|', 1) == "F")
        tone(buzzerPin, getText(received, '|', 2).toInt());
    }
    else if (mode == "CNT") {
      counterAllLED = 0;
      if (getText(received, '|', 1) == "LED")
        counterLED(getText(received, '|', 2).toInt());
      else if (getText(received, '|', 1) == "ALL")
        counterAllLED = 1;
      else if (getText(received, '|', 1) == "VCC")
        digitalWrite(counterVcc, getText(received, '|', 2).toInt());
      else if (getText(received, '|', 1) == "CLK")
        digitalWrite(clockPin, getText(received, '|', 2).toInt());
      else if (getText(received, '|', 1) == "RST")
        digitalWrite(resetPin, getText(received, '|', 2).toInt());
      if (counterAllLED)
        counterInitialize();
    }
    else if (mode == "RGB") {
      RGBcoloursEnable = 0;
      RGB(getText(received, '|', 1).toInt(), getText(received, '|', 2).toInt(), getText(received, '|', 3).toInt());
    }
    else if (mode == "TRGB") {
      RGB_TIME = getText(received, '|', 1).toInt();
      RGBcoloursEnable = 1;
    }
    else if (mode == "RGB2") {
      RGB2coloursEnable = 0;
      RGB2(getText(received, '|', 1).toInt(), getText(received, '|', 2).toInt(), getText(received, '|', 3).toInt(), getText(received, '|', 4).toInt());
    }
    else if (mode == "TRGB2") {
      RGB2_TIME = getText(received, '|', 1).toInt();
      RGB2coloursEnable = 1;
    }
    else if (mode == "LEDr") {
      digitalWrite(LEDr, getText(received, '|', 1).toInt());
    }
    else if (mode == "LEDg") {
      digitalWrite(LEDg, getText(received, '|', 1).toInt());
    }
    else if (mode == "LEDb") {
      digitalWrite(LEDb, getText(received, '|', 1).toInt());
    }
  }
  if (counterAllLED)  {
    digitalWrite(clockPin, 1);
    digitalWrite(clockPin, 0);
  }
  if (RGBcoloursEnable)  {
    if (millis() - t2 >= RGB_TIME)  {
      RGBcolours();
      RGB(redValue, greenValue, blueValue);
      t2 = millis();
    }
  }
  if (RGB2coloursEnable)  {
    if (millis() - t3 >= RGB2_TIME)  {
      RGB2colours();
      RGB2(RGBvalue, redState, greenState, blueState);
      t3 = millis();
    }
  }
}

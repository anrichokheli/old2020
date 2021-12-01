#define RGBred D6
#define RGBgreen D7
#define RGBblue D8
#define A D0
#define B D1
#define C D2
#define redPin D3
#define greenPin D4
#define bluePin D5
#define input A0

byte LED_N = 1;
byte redValue[8] = {0, 255, 255, 0, 0, 0, 255, 255};
byte greenValue[8] = {0, 0, 255, 255, 255, 0, 0, 255};
byte blueValue[8] = {0, 0, 0, 0, 255, 255, 255, 255};
int redChange[8] = {0, 0, -1, 0, 0, 1, 0, 0};
int greenChange[8] = {0, 1, 0, 0, -1, 0, 1, 0};
int blueChange[8] = {0, 0, 0, 1, 0, 0, 0, -1};
boolean repeat[8];
byte RED1;
byte GREEN1;
byte BLUE1;
byte N;
unsigned long t;
byte RED2;
byte GREEN2;
byte BLUE2;
byte RGBrandomValues[3];
byte RGB8randomValues[8][3];
byte mode;
boolean pinState;
boolean state;
unsigned long t2;
unsigned long t3;
byte LEDindex = 1;
boolean LEDdirection = 1;
unsigned long t4;
byte intensity;
unsigned long t5;
unsigned long t6;
byte LEDi = 1;
boolean LEDd = 1;
byte intensity2;
unsigned long t7;
byte LEDi2;
byte valueR;
byte valueG;
byte valueB;
byte valuesMode;
unsigned long t8;
unsigned long t9;
byte RGB8mode;
unsigned long t10;

void RGB(byte n, byte red, byte green, byte blue)  {
  n--;
  digitalWrite(A, n & 1);
  digitalWrite(B, n & (1 << 1));
  digitalWrite(C, n & (1 << 2));
  analogWrite(RGBred, red);
  analogWrite(RGBgreen, green);
  analogWrite(RGBblue, blue);
}

void colorsTransition() {
  if ((redValue[LED_N - 1] == 0) && (greenValue[LED_N - 1] == 0) && (blueValue[LED_N - 1] == 0) && (redChange[LED_N - 1] == 0) && (greenChange[LED_N - 1] == 0) && (blueChange[LED_N - 1] == 0))  {
    redChange[LED_N - 1] = 1;
  }
  else if (((redValue[LED_N - 1] == 255) && (greenValue[LED_N - 1] == 0) && (blueValue[LED_N - 1] == 0) && (redChange[LED_N - 1] == 1) && (greenChange[LED_N - 1] == 0) && (blueChange[LED_N - 1] == 0)) || repeat[LED_N - 1]) {
    redChange[LED_N - 1] = 0;
    greenChange[LED_N - 1] = 1;
    repeat[LED_N - 1] = 0;
  }
  else if ((redValue[LED_N - 1] == 255) && (greenValue[LED_N - 1] == 255) && (blueValue[LED_N - 1] == 0) && (redChange[LED_N - 1] == 0) && (greenChange[LED_N - 1] == 1) && (blueChange[LED_N - 1] == 0)) {
    greenChange[LED_N - 1] = 0;
    redChange[LED_N - 1] = -1;
  }
  else if ((redValue[LED_N - 1] == 0) && (greenValue[LED_N - 1] == 255) && (blueValue[LED_N - 1] == 0) && (redChange[LED_N - 1] == -1) && (greenChange[LED_N - 1] == 0) && (blueChange[LED_N - 1] == 0)) {
    redChange[LED_N - 1] = 0;
    blueChange[LED_N - 1] = 1;
  }
  else if ((redValue[LED_N - 1] == 0) && (greenValue[LED_N - 1] == 255) && (blueValue[LED_N - 1] == 255) && (redChange[LED_N - 1] == 0) && (greenChange[LED_N - 1] == 0) && (blueChange[LED_N - 1] == 1)) {
    blueChange[LED_N - 1] = 0;
    greenChange[LED_N - 1] = -1;
  }
  else if ((redValue[LED_N - 1] == 0) && (greenValue[LED_N - 1] == 0) && (blueValue[LED_N - 1] == 255) && (redChange[LED_N - 1] == 0) && (greenChange[LED_N - 1] == -1) && (blueChange[LED_N - 1] == 0)) {
    greenChange[LED_N - 1] = 0;
    redChange[LED_N - 1] = 1;
  }
  else if ((redValue[LED_N - 1] == 255) && (greenValue[LED_N - 1] == 0) && (blueValue[LED_N - 1] == 255) && (redChange[LED_N - 1] == 1) && (greenChange[LED_N - 1] == 0) && (blueChange[LED_N - 1] == 0)) {
    redChange[LED_N - 1] = 0;
    greenChange[LED_N - 1] = 1;
  }
  else if ((redValue[LED_N - 1] == 255) && (greenValue[LED_N - 1] == 255) && (blueValue[LED_N - 1] == 255) && (redChange[LED_N - 1] == 0) && (greenChange[LED_N - 1] == 1) && (blueChange[LED_N - 1] == 0)) {
    greenChange[LED_N - 1] = 0;
    blueChange[LED_N - 1] = -1;
  }
  else if ((redValue[LED_N - 1] == 255) && (greenValue[LED_N - 1] == 255) && (blueValue[LED_N - 1] == 0) && (redChange[LED_N - 1] == 0) && (greenChange[LED_N - 1] == 0) && (blueChange[LED_N - 1] == -1)) {
    blueChange[LED_N - 1] = 0;
    greenChange[LED_N - 1] = -1;
  }
  else if ((redValue[LED_N - 1] == 255) && (greenValue[LED_N - 1] == 0) && (blueValue[LED_N - 1] == 0) && (redChange[LED_N - 1] == 0) && (greenChange[LED_N - 1] == -1) && (blueChange[LED_N - 1] == 0)) {
    greenChange[LED_N - 1] = 0;
    repeat[LED_N - 1] = 1;
  }
  redValue[LED_N - 1] += redChange[LED_N - 1];
  greenValue[LED_N - 1] += greenChange[LED_N - 1];
  blueValue[LED_N - 1] += blueChange[LED_N - 1];
}

void RGB2020()  {
  RGB(LED_N, redValue[LED_N - 1], greenValue[LED_N - 1], blueValue[LED_N - 1]);
  RGB2(redValue[0], greenValue[0], blueValue[0]);
  colorsTransition();
  if (++LED_N > 8)
    LED_N = 1;
}

void RGB2(byte r, byte g, byte b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

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

void RGB2020_2()  {
  RGB(LED_N, redValue[0], greenValue[0], blueValue[0]);
  RGB2(redValue[0], greenValue[0], blueValue[0]);
  colorsTransition();
  if (++LED_N > 8)
    LED_N = 1;
}

void RGB2020_3()  {
  switch (LED_N)  {
    case 1:
      RGB(LED_N, greenValue[0], redValue[0], blueValue[0]);
      break;
    case 2:
      RGB(LED_N, redValue[0], blueValue[0], greenValue[0]);
      break;
    case 3:
      RGB(LED_N, blueValue[0], greenValue[0], redValue[0]);
      break;
    case 4:
      RGB(LED_N, greenValue[0], blueValue[0], redValue[0]);
      break;
    case 5:
      RGB(LED_N, blueValue[0], redValue[0], greenValue[0]);
      break;
    case 6:
      RGB(LED_N, 255 - redValue[0], 255 - blueValue[0], 255 - greenValue[0]);
      break;
    case 7:
      RGB(LED_N, 255 - greenValue[0], 255 - redValue[0], 255 - blueValue[0]);
      break;
    case 8:
      RGB(LED_N, 255 - blueValue[0], 255 - redValue[0], 255 - greenValue[0]);
      break;
  }
  RGB2(redValue[0], greenValue[0], blueValue[0]);
  colorsTransition();
  if (++LED_N > 8)
    LED_N = 1;
}

void RGBrandom()  {
  if (millis() - t >= 50)  {
    for (byte i = 0; i < 3; i++) {
      RGBrandomValues[i] = random(0, 256);
    }
    for (byte j = 0; j < 8; j++) {
      for (byte i = 0; i < 3; i++) {
        RGB8randomValues[j][i] = random(0, 256);
      }
    }
    t = millis();
  }
  RGB(LED_N, RGB8randomValues[LED_N][0], RGB8randomValues[LED_N][1], RGB8randomValues[LED_N][2]);
  RGB2(RGBrandomValues[0], RGBrandomValues[1], RGBrandomValues[2]);
  if (++LED_N > 8)
    LED_N = 1;
}

void RGB8ALL(byte redColour, byte greenColour, byte blueColour)  {
  RGB(LED_N, redColour, greenColour, blueColour);
  if (++LED_N > 8)
    LED_N = 1;
}

void LEDs0()  {
  digitalWrite(RGBred, 0);
  digitalWrite(RGBgreen, 0);
  digitalWrite(RGBblue, 0);
  digitalWrite(redPin, 0);
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
}

void setValues(byte r, byte g, byte b)  {
  valueR = r;
  valueG = g;
  valueB = b;
}

void setup()  {
  pinMode(RGBred, OUTPUT);
  pinMode(RGBgreen, OUTPUT);
  pinMode(RGBblue, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(input, INPUT);
}

void loop() {
  if (((millis() - t > 1000) && (micros() - t10 >= 900)) || (mode == 4))  {
    pinState = (analogRead(input) < 250);
    t10 = micros();
  }
  if (pinState && !state)  {
    if (++mode == 10)  {
      LEDs0();
      mode = 0;
    }
    state = 1;
  }
  else if (!pinState && state) {
    state = 0;
    t = millis();
  }
  if (mode == 1)  {
    if (millis() - t2 >= 1)  {
      RGB2020_2();
      t2 = millis();
    }
  }
  else if (mode == 2) {
    RGB2020();
  }
  else if (mode == 3) {
    RGB2020_3();
  }
  else if (mode == 4) {
    RGBrandom();
  }
  else if (mode == 5) {
    if (millis() - t9 >= 500)  {
      if (++RGB8mode == 8)
        RGB8mode = 1;
      t9 = millis();
    }
    if (RGB8mode == 1)  {
      RGB2(255, 0, 0);
      RGB8ALL(255, 0, 0);
    }
    else if (RGB8mode == 2) {
      RGB2(255, 255, 0);
      RGB8ALL(255, 255, 0);
    }
    else if (RGB8mode == 3) {
      RGB2(0, 255, 0);
      RGB8ALL(0, 255, 0);
    }
    else if (RGB8mode == 4) {
      RGB2(0, 255, 255);
      RGB8ALL(0, 255, 255);
    }
    else if (RGB8mode == 5) {
      RGB2(0, 0, 255);
      RGB8ALL(0, 0, 255);
    }
    else if (RGB8mode == 6) {
      RGB2(255, 0, 255);
      RGB8ALL(255, 0, 255);
    }
    else if (RGB8mode == 7) {
      RGB2(255, 255, 255);
      RGB8ALL(255, 255, 255);
    }
  }
  else if (mode == 6) {
    if (millis() - t3 >= 250)  {
      switch (LEDindex)  {
        case 1:
          RGB(LEDindex, 255, 0, 0);
          RGB2(255, 0, 0);
          break;
        case 2:
          RGB(LEDindex, 255, 255, 0);
          RGB2(255, 255, 0);
          break;
        case 3:
          RGB(LEDindex, 0, 255, 0);
          RGB2(0, 255, 0);
          break;
        case 4:
          RGB(LEDindex, 0, 255, 255);
          RGB2(0, 255, 255);
          break;
        case 5:
          RGB(LEDindex, 0, 0, 255);
          RGB2(0, 0, 255);
          break;
        case 6:
          RGB(LEDindex, 255, 0, 255);
          RGB2(255, 0, 255);
          break;
        case 7:
          RGB(LEDindex, 255, 255, 255);
          RGB2(255, 255, 255);
          break;
        case 8:
          RGB(LEDindex, 64, 128, 255);
          RGB2(64, 128, 255);
          break;
      }
      if (LEDdirection)
        LEDindex++;
      else
        LEDindex--;
      if (LEDindex > 8)  {
        LEDdirection = 0;
        LEDindex = 7;
      }
      else if (LEDindex < 1) {
        LEDdirection = 1;
        LEDindex = 2;
      }
      t3 = millis();
    }
  }
  else if (mode == 7) {
    if (micros() - t4 >= 500)  {
      if (intensity < 255)
        intensity++;
      switch (LEDindex)  {
        case 1:
          RGB(LEDindex, intensity, 0, 0);
          RGB2(intensity, 0, 0);
          break;
        case 2:
          RGB(LEDindex, intensity, intensity, 0);
          RGB2(intensity, intensity, 0);
          break;
        case 3:
          RGB(LEDindex, 0, 255, 0);
          RGB2(0, intensity, 0);
          break;
        case 4:
          RGB(LEDindex, 0, 255, 255);
          RGB2(0, intensity, intensity);
          break;
        case 5:
          RGB(LEDindex, 0, 0, intensity);
          RGB2(0, 0, intensity);
          break;
        case 6:
          RGB(LEDindex, intensity, 0, intensity);
          RGB2(intensity, 0, intensity);
          break;
        case 7:
          RGB(LEDindex, intensity, intensity, intensity);
          RGB2(intensity, intensity, intensity);
          break;
        case 8:
          RGB(LEDindex, map(intensity, 0, 255, 0, 64), map(intensity, 0, 255, 0, 128), intensity);
          RGB2(map(intensity, 0, 255, 0, 64), map(intensity, 0, 255, 0, 128), intensity);
          break;
      }
      t4 = micros();
    }
    if (millis() - t5 >= 250)  {
      intensity = 0;
      if (LEDdirection)
        LEDindex++;
      else
        LEDindex--;
      if (LEDindex > 8)  {
        LEDdirection = 0;
        LEDindex = 7;
      }
      else if (LEDindex < 1) {
        LEDdirection = 1;
        LEDindex = 2;
      }
      t5 = millis();
    }
  }
  if (mode == 8)  {
    if (micros() - t4 >= 500)  {
      if (micros() % 2)
        LEDi2 = 9 - LEDi;
      else
        LEDi2 = LEDi;
      if (intensity2 < 255)
        intensity2++;
      switch (LEDi2)  {
        case 1:
          RGB(LEDi2, intensity2, map(intensity2, 0, 255, 0, 127), 0);
          RGB2(intensity2, map(intensity2, 0, 255, 0, 127), 0);
          break;
        case 2:
          RGB(LEDi2, map(intensity2, 0, 255, 0, 127), intensity2, 0);
          RGB2(map(intensity2, 0, 255, 0, 127), intensity2, 0);
          break;
        case 3:
          RGB(LEDi2, 0, map(intensity2, 0, 255, 0, 127), intensity2);
          RGB2(0, map(intensity2, 0, 255, 0, 127), intensity2);
          break;
        case 4:
          RGB(LEDi2, 0, intensity2, map(intensity2, 0, 255, 0, 127));
          RGB2(0, intensity2, map(intensity2, 0, 255, 0, 127));
          break;
        case 5:
          RGB(LEDi2, map(intensity2, 0, 255, 0, 127), 0, map(intensity2, 0, 255, 0, 127));
          RGB2(map(intensity2, 0, 255, 0, 127), 0, map(intensity2, 0, 255, 0, 127));
          break;
        case 6:
          RGB(LEDi2, map(intensity2, 0, 255, 0, 127), intensity2, map(intensity2, 0, 255, 0, 127));
          RGB2(map(intensity2, 0, 255, 0, 127), intensity2, map(intensity2, 0, 255, 0, 127));
          break;
        case 7:
          RGB(LEDi2, intensity2, intensity2, map(intensity2, 0, 255, 0, 127));
          RGB2(intensity2, intensity2, map(intensity2, 0, 255, 0, 127));
          break;
        case 8:
          RGB(LEDi2, map(intensity2, 0, 255, 0, 127), intensity2, intensity2);
          RGB2(map(intensity2, 0, 255, 0, 127), intensity2, intensity2);
          break;
      }
      t4 = micros();
    }
    if (millis() - t7 >= 250)  {
      intensity2 = 0;
      if (LEDd)
        LEDi++;
      else
        LEDi--;
      if (LEDi > 4)  {
        LEDd = 0;
        LEDi = 3;
      }
      else if (LEDi < 1) {
        LEDd = 1;
        LEDi = 2;
      }
      t7 = millis();
    }
  }
  if (mode == 9)  {
    if (micros() - t4 >= 500)  {
      if (micros() % 2) {
        LEDi2 = 9 - LEDi;
        if (valuesMode == 0)
          setValues(0, 0, 255);
        else if (valuesMode == 1)
          setValues(0, 255, 255);
        else if (valuesMode == 2)
          setValues(255, 255, 0);
        else if (valuesMode == 3)
          setValues(255, 255, 255);
      }
      else  {
        LEDi2 = LEDi;
        if (valuesMode == 0)
          setValues(255, 0, 0);
        else if (valuesMode == 1)
          setValues(0, 255, 0);
        else if (valuesMode == 2)
          setValues(255, 0, 255);
        else if (valuesMode == 3)
          setValues(255, 127, 0);
      }
      if (intensity2 < 255)
        intensity2++;
      switch (LEDi2)  {
        case 1:
          RGB(LEDi2, map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          RGB2(map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          break;
        case 2:
          RGB(LEDi2, map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          RGB2(map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          break;
        case 3:
          RGB(LEDi2, map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          RGB2(map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          break;
        case 4:
          RGB(LEDi2, map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          RGB2(map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          break;
        case 5:
          RGB(LEDi2, map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          RGB2(map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          break;
        case 6:
          RGB(LEDi2, map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          RGB2(map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          break;
        case 7:
          RGB(LEDi2, map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          RGB2(map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          break;
        case 8:
          RGB(LEDi2, map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          RGB2(map(intensity2, 0, 255, 0, valueR), map(intensity2, 0, 255, 0, valueG), map(intensity2, 0, 255, 0, valueB));
          break;
      }
      t4 = micros();
    }
    if (millis() - t7 >= 250)  {
      intensity2 = 0;
      if (LEDd)
        LEDi++;
      else
        LEDi--;
      if (LEDi > 8)  {
        LEDd = 0;
        LEDi = 7;
      }
      else if (LEDi < 1) {
        LEDd = 1;
        LEDi = 2;
        if (++valuesMode == 4)
          valuesMode = 0;
      }
      t7 = millis();
    }
  }
}

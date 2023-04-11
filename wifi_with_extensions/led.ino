const int pinoLEDR = 9;
const int pinoLEDG = 8;
const int pinoLEDB = 7;

const int maxLED = 150;
const int minLED = 0;

void setupLED() {
  pinMode(pinoLEDR, OUTPUT);
  pinMode(pinoLEDG, OUTPUT);
  pinMode(pinoLEDB, OUTPUT);
}

void blink() {
  Serial.println("blinking...");
  turnLightsOff();
  delay(300);

  if (status == 301) {
    Serial.println("Meeting in the next 5 minutes");
    blue();
  } else if (status == 401) {
    Serial.println("Meeting in happening now");
    red();
  } else if (status == 200) {
    Serial.println("No meetings");
    green();
  }
}

void turnLightsOff() {
  analogWrite(pinoLEDR, minLED);
  analogWrite(pinoLEDG, minLED);
  analogWrite(pinoLEDB, minLED);
}

void red() {
  analogWrite(pinoLEDR, maxLED);
  analogWrite(pinoLEDG, minLED);
  analogWrite(pinoLEDB, minLED);
}

void green() {
  analogWrite(pinoLEDG, maxLED);
  analogWrite(pinoLEDR, minLED);
  analogWrite(pinoLEDB, minLED);
}

void blue() {
  analogWrite(pinoLEDB, maxLED);
  analogWrite(pinoLEDG, minLED);
  analogWrite(pinoLEDR, maxLED);
}

void white() {
  analogWrite(pinoLEDB, maxLED);
  analogWrite(pinoLEDG, maxLED);
  analogWrite(pinoLEDR, maxLED);
}
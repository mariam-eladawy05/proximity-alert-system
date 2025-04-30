#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 9;
const int echoPin = 10;
const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 4;
const int buzzer = 5;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust 0x27 if your LCD uses a different address

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin();
  lcd.backlight();
  lcd.print("Proximity Alert");
  delay(2000);
  lcd.clear();
}

void loop() {
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm  ");

  if (distance < 10) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);
  } else if (distance < 20) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, LOW);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
  }

  delay(200);
}

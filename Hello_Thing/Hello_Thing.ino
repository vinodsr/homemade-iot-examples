
#include <LiquidCrystal_SR.h>
#include "pitches.h"

LiquidCrystal_SR lcd(2, 10, 9);
//                   | |  |-SCK Pin
//                   | \-- Clock Pin
//                   \---- Data/Enable Pin

int isObstaclePin = A0;  // This is our input pin
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE
int LED = 13; // Use the onboard Uno LED

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_C4,NOTE_C4, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4, 4, 8, 8, 4, 4, 4, 4, 4
};

const int BUZZ_PIN = 8;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
}

void display(String message) {
  lcd.setCursor(0, 0);
  lcd.print(message);

}

void alarm() {
  for (int thisNote = 0; thisNote < 16; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 500 / noteDurations[thisNote];
    tone(BUZZ_PIN, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZ_PIN);
  }
}
void loop() {
  isObstacle = analogRead(isObstaclePin);
  Serial.println(isObstacle);
  if (isObstacle == LOW)
  {
    display("Caught");
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    alarm();
  }
  else
  {
    display("OK");
    Serial.println("clear");
    digitalWrite(LED, LOW);
  }
  delay(100);
  lcd.clear();
}


#include <LiquidCrystal_SR.h>

LiquidCrystal_SR lcd(2, 10, 9); 
//                   | |  |-SCK Pin
//                   | \-- Clock Pin
//                   \---- Data/Enable Pin


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  lcd.print("DevOPS");
  // set the cursor to (16,1):
  lcd.setCursor(0, 1);

  // print from 0 to 9:
  lcd.print("Deploying Code");


  delay(4000);

  // clear screen for the next loop:
  lcd.clear();
}

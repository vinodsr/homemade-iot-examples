

int LED = 13; // Use the onboard Uno LED
int isObstaclePin = A0;  // This is our input pin
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE



void setup() {
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);

}

void loop() {
  isObstacle = analogRead(isObstaclePin);
  Serial.println(isObstacle);
  if (isObstacle == LOW)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("clear");
    digitalWrite(LED, LOW);
  }
  delay(200);
}


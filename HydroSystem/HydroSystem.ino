/*
  Water Tracking System
  Modified Code: Kenyang Lual
  Date: 12/01/2024
*/

#include <LiquidCrystal.h>
//#include <HCSR04.h> 

// Pin assignments for the LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Create an LCD object
//LiquidCrystal lcd(rs, enable, d4, d5, d6, d7); 

// Pin assignments for the ultrasonic sensor
const int trigPin = 12;
const int echoPin = 13;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16, 2);

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Welcome message on LCD
  lcd.print("HydroHomie Water Tracker!");
  delay(2000);
  lcd.clear();
}

 //Measure the distance using the ultrasonic sensor
long measureDistance() {
  long duration;

  // Trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  long distance = duration * 0.034 / 2;
  return distance;
}

// Calculate the volume of water in the tank
float calculateVolume(long distance) {
  float tankHeight = 24.3; // Prone to be changed once we have accurate container measurements
  float radius = 12;      // // Prone to be changed once we have accurate container measurements
  float liquidHeight = tankHeight - distance;

  // Ensure liquidHeight is not negative
  if (liquidHeight < 0) {
    liquidHeight = 0;
  }

  // Calculate volume in liters
  float volume = 3.14 * radius * radius * liquidHeight / 1000.0;
  return volume;
}

void loop() {
  // Measure distance
  long distance = measureDistance();
  float volume = calculateVolume(distance);

  // Display on LCD
  lcd.clear();
  //position the cursor at col 0 row 0
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");

  //position the cursor at col 0 row 1
  lcd.setCursor(0, 1);
  lcd.print("Vol: ");
  lcd.print(volume);
  lcd.print(" L");

  // Print to Serial Monitor in case LCD board fails
  // Optional in case LCD board fails/battery dies
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Volume: ");
  Serial.print(volume);
  Serial.println(" L");

  delay(1000); // Update every second
} 

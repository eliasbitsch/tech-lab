// Include the necessary libraries for LCD and time keeping
#include <LiquidCrystal.h>
#include <TimeLib.h>

// Define the pins for LED and Tastschalter
#define LED_PIN 8
#define TASTER_PIN_1 6
#define TASTER_PIN_2 7

// Define the LCD pins and create an instance of the LiquidCrystal library
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define variables for storing the start time and reaction time
unsigned long startTime;
unsigned long reactionTime;
int firstTaster = 0;
String firstTaster_;

void setup() {
  // Initialize the LCD and set the cursor to the top-left corner
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  // Initialize the LED and Tastschalter pins as input/output and enable the internal pull-up resistors
  pinMode(LED_PIN, OUTPUT);
  pinMode(TASTER_PIN_1, INPUT_PULLUP);
  pinMode(TASTER_PIN_2, INPUT_PULLUP);

  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  // Wait for both Tastschalter to be pressed at the same time to start the test
  while (digitalRead(TASTER_PIN_1) == HIGH || digitalRead(TASTER_PIN_2) == HIGH) {
    delay(10);
  }

  // Blink the LED to signal the start of the test
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);

  // Wait for a random amount of time between 2 and 3 seconds
  delay(random(2000, 3000));

  // Turn on the LED and record the start time
  digitalWrite(LED_PIN, HIGH);
  startTime = millis();

  // Wait for the Tastschalter to be pressed and record which one was pressed first
  while (digitalRead(TASTER_PIN_1) == HIGH && digitalRead(TASTER_PIN_2) == HIGH) {
    delay(10);
  }
  if (digitalRead(TASTER_PIN_1) == LOW) {
    firstTaster = 1;
    firstTaster_ = "rechts";
  } else {
    firstTaster = 2;
    firstTaster_ = "links";
  }

  // Record the reaction time and turn off the LED
  reactionTime = millis() - startTime;
  digitalWrite(LED_PIN, LOW);

  // Display the reaction time and which Tastschalter was pressed first on the LCD
  lcd.clear();
  lcd.print("Reaction time:");
  lcd.setCursor(0, 1);
  lcd.print(reactionTime);
  lcd.print(" ms");
  lcd.setCursor(9, 1);
  lcd.print(firstTaster_);

  // Wait for a few seconds before clearing the LCD and starting the test again
  delay(5000);
  lcd.clear();
}

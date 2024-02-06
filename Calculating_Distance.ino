// Define pins for ultrasonic sensor
int trigPin = 3;  // Connect the trig pin of the ultrasonic sensor to digital pin 9
int echoPin = 4; // Connect the echo pin of the ultrasonic sensor to digital pin 10

// Define pins for LEDs
int redLed = 7;    // Connect red LED to digital pin 2
int yellowLed = 6; // Connect yellow LED to digital pin 3
int greenLed = 5;  // Connect green LED to digital pin 4

// Define pin for the buzzer
int buzzerPin = 8; // Connect the buzzer to digital pin 5

// Define threshold distances for LED and buzzer control
int farDistance = 30;   // Distance for green LED
int closeDistance = 20; // Distance for yellow LED and buzzer
int tooCloseDistance = 10; // Distance for red LED and continuous buzzer

void setup() {
  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set LED pins as output
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin to calculate distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Print distance to Serial Monitor (optional)
  Serial.print("Distance: ");
  Serial.println(distance);

  /// Control LEDs and buzzer based on distance
  if (distance > farDistance) {
    // Car is very far, display green LED
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    noTone(buzzerPin);
  } else if (distance <= farDistance && distance > closeDistance) {
    // Car is getting close, display yellow LED
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
    noTone(buzzerPin);
  } else if (distance <= closeDistance && distance > tooCloseDistance) {
    // Car is too close, display red LED and beep the buzzer
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
    tone(buzzerPin, 1000); // Activate buzzer with a frequency of 1000 Hz
  } else {
    // Car is too close, display red LED and continuous buzzer
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
    tone(buzzerPin, 1000); // Activate buzzer with a frequency of 1000 Hz
  }

  // Add a delay for stability
  delay(500);
}
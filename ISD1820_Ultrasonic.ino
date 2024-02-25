const int trigPin = 5;
const int echoPin = 18;
const int ledPin = 2; // Pin to which the LED is connected

const int ISD_PIN = 4; // ISD1820 module PE Pin


long duration;
float distanceCm;
unsigned long startTime; 



void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledPin, OUTPUT); // Sets the ledPin as an Output

  pinMode(ISD_PIN, OUTPUT);  // Don't forget to set ISD_PIN as OUTPUT
  digitalWrite(ledPin, LOW);  
  digitalWrite(ISD_PIN, LOW);  // Initialize ISD_PIN to LOW
  // Serial.begin(9600); // Initialize serial communication
  Serial.println("Distance Alert System Initialized");
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  distanceCm = duration * 0.034 / 2; // Assuming speed of sound is approximately 34 cm/ms
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  // Blink the LED on pin 2 if the distance is less than a certain value (adjust as needed)
 // Blink the LED on pin 2 and set the new data pin high if the distance is less than a certain value (adjust as needed)
  if (distanceCm < 10) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(ISD_PIN, HIGH);  // Set the new data pin high
    startTime = millis();  // Record the start time
    while (millis() - startTime < 10000) {
      // Keep the LED and new data pin on for 10 seconds
    }
    digitalWrite(ledPin, LOW);
    digitalWrite(ISD_PIN, LOW);  // Set the new data pin back to LOW
  } else {
    digitalWrite(ledPin, LOW); // Make sure the LED is off if the distance is greater than or equal to 10 cm
    digitalWrite(ISD_PIN, LOW);  // Make sure the new data pin is off if the distance is greater than or equal to 10 cm
  }

  delay(1000);


}

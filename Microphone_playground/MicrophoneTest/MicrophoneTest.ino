// Define the constants
const int AnalogPin = A0;  // Input pin for the Microphone 
const int DigitalPin = 53; // Input pin for the Microphone

const int LedRedPin1 = 2;    // LED for Digital signal
const int LedGreenPin2 = 3;  // LED for Analog signal threshold

const int analogThreshold = 518;  // Threshold for analog signal to turn on green LED
// NOTE: The threshold should be 512. But to avoid it being too sensitve and add a 
//       bit of calibration leeway we just add a bit more. 

// Define the variables 
int analogValue;
int digitalValue;

void setup() {
  Serial.begin(9600);

  // Setting up LED output pins
  pinMode(LedRedPin1, OUTPUT);
  pinMode(LedGreenPin2, OUTPUT);

  // Setting up input pins for microphone signals
  pinMode(AnalogPin, INPUT);
  pinMode(DigitalPin, INPUT);
}

void loop() {
  // Read sensor values
  analogValue = analogRead(AnalogPin);
  digitalValue = digitalRead(DigitalPin);

  // Output both values to the Serial Plotter
  Serial.print(digitalValue);   // Print digital value (0 or 1)
  Serial.print("\t");           // Tab to separate the values
  Serial.println(analogValue);  // Print analog value and move to the next line

  // Turn on the red LED based on the digital signal
  if (digitalValue == 1) {
    digitalWrite(LedRedPin1, HIGH);
  } else {
    digitalWrite(LedRedPin1, LOW);
  }

  // Turn on the green LED if the analog signal exceeds the threshold
  if (analogValue > analogThreshold) {
    digitalWrite(LedGreenPin2, HIGH);
  } else {
    digitalWrite(LedGreenPin2, LOW);
  }

}

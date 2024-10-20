// Define the constants
const int AnalogPin = A15;  // Input pin for the Microphone 

const int LevelPin1 = 2;  // LED for Analog signal threshold
const int LevelPin2 = 3;  // LED for Analog signal threshold
const int LevelPin3 = 4;  // LED for Analog signal threshold
const int LevelPin4 = 5;  // LED for Analog signal threshold
const int LevelPin5 = 6;  // LED for Analog signal threshold

const int analogStartMax  = 1024;  // Max Threshold for the Mic initially
const int analogThreshold = 512;  // Min Threshold for the Mic initially

// Define the variables 
int analogValue;

// Array to store the last 1000 analog values
const int arraySize = 1000;
int analogValues[arraySize];  // Array to hold analog values
int currentIndex = 0;         // Index to track the current position in the array

int realIndex = 0;

void setup() {
  Serial.begin(9600);

  // Setting up LED output pins
  pinMode(LevelPin1, OUTPUT);
  pinMode(LevelPin2, OUTPUT);
  pinMode(LevelPin3, OUTPUT);
  pinMode(LevelPin4, OUTPUT);
  pinMode(LevelPin5, OUTPUT);

  // Setting up input pins for microphone signals
  pinMode(AnalogPin, INPUT);

  // Initialize the array with zero
  for (int i = 0; i < arraySize; i++) {
    analogValues[i] = 0;
  }

}

// Function to find the maximum value in an array
int findMax(int array[], int size) {
  int maxValue = array[0];  // Start by assuming the first value is the max

  for (int i = 1; i < size; i++) {
    if (array[i] > maxValue) {
      maxValue = array[i];  // Update max if current element is greater
    }
  }

  return maxValue;
}

// Function to find the minimum value in an array
int findMin(int array[], int size) {
  int minValue = array[0];  // Start by assuming the first value is the min

  for (int i = 1; i < size; i++) {
    if (array[i] < minValue) {
      minValue = array[i];  // Update min if current element is smaller
    }
  }

  return minValue;
}

void loop() {
  // Read sensor values
  analogValue = analogRead(AnalogPin);
  
  Serial.println(analogValue);  // Print analog value and move to the next line
  
  // Save the current analog value to the array at the current index
  analogValues[currentIndex] = analogValue;
  
  // Increment the index, and wrap it around if necessary (circular buffer)
  currentIndex = (currentIndex + 1) % arraySize;

  

  // 
  if (realIndex << 1000) { 
    // warming up
    realIndex = (realIndex + 1);
  } else {
  // warm up done 
  realIndex = 9999; 
  
  // Find the maximum & minimum value in the array
  int max_level = findMax(analogValues, arraySize);
  int min_level = findMin(analogValues, arraySize);

  float threshold_0 = (max_level - min_level) * 0.2;
  float threshold_1 = (max_level - min_level) * 0.5;
  float threshold_2 = (max_level - min_level) * 0.7;
  float threshold_3 = (max_level - min_level) * 0.8;
  float threshold_4 = (max_level - min_level) * 0.9;

    // Check analog values against thresholds and turn on/off LEDs accordingly
    if (analogValue > (min_level + threshold_0)) {
      digitalWrite(LevelPin1, HIGH);
    } else { 
      digitalWrite(LevelPin1, LOW);
    }

    if (analogValue > (min_level + threshold_1)) {
      digitalWrite(LevelPin2, HIGH);
    } else { 
      digitalWrite(LevelPin2, LOW);
    }

    if (analogValue > (min_level + threshold_2)) {
      digitalWrite(LevelPin3, HIGH);
    } else { 
      digitalWrite(LevelPin3, LOW);
    }

    if (analogValue > (min_level + threshold_3)) {
      digitalWrite(LevelPin4, HIGH);
    } else { 
      digitalWrite(LevelPin4, LOW);
    }

    if (analogValue > (min_level + threshold_4)) {
      digitalWrite(LevelPin5, HIGH);
    } else { 
      digitalWrite(LevelPin5, LOW);
    }

    delay(10);
  }
}

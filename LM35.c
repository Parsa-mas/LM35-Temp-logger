// Define the sensor pin (LM35 is connected to analog pin A0)
#define sensorPin A0

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Set the analog reference to the default (5V for most Arduino boards)
  analogReference(DEFAULT);  
}

void loop() {
  int sampleCount = 10; // Number of samples to average for better accuracy
  float sum = 0; // Variable to accumulate sensor readings

  // Take multiple readings to reduce noise and get a more accurate value
  for (int i = 0; i < sampleCount; i++) {
    sum += analogRead(sensorPin); // Read the sensor value
    delay(10); // Small delay to stabilize the sensor reading
  }

  // Calculate the average reading from all the samples
  float averageReading = sum / sampleCount;

  // Check if the sensor is connected properly (LM35 gives a value between 10-1015 on a 5V system)
  if (averageReading < 10 || averageReading > 1015) {
    // Print error message if sensor is out of range or not connected
    Serial.println("Error: Sensor not connected or malfunctioning!");
  } else {
    // Convert the analog reading to voltage (5V system, use 3.3V if using 3.3V system)
    float voltage = averageReading * (5.0 / 1024.0);  
    // Convert voltage to temperature in Celsius (LM35 gives 10mV per °C)
    float temperatureC = voltage * 100.0;

    // Print the raw reading, voltage, and temperature in Celsius
    Serial.print("Raw Reading: ");
    Serial.println(averageReading);
    Serial.print("Voltage: ");
    Serial.println(voltage);
    Serial.print("Temperature (C): ");
    Serial.print(temperatureC);
    Serial.println("°C");

    // Convert Celsius to Fahrenheit
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    // Print temperature in Fahrenheit
    Serial.print("Temperature (F): ");
    Serial.print(temperatureF);
    Serial.println("°F");
  }

  // Wait for 1 second before the next reading
  delay(1000);
}

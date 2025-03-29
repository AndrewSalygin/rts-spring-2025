volatile uint32_t totalInterval = 0;
volatile uint32_t totalSquaredInterval = 0;
volatile uint32_t previousTime = 0;
volatile unsigned int numSamples = 0;
const unsigned int maxMeasurements = 42;

void setup() {
  Serial.begin(115200);
  pinMode(21, INPUT);
  attachInterrupt(digitalPinToInterrupt(21), calculateInterval, CHANGE);
}

void loop() {
  if (numSamples >= maxMeasurements) {
    noInterrupts();
    uint32_t accumulatedInterval = totalInterval;
    uint32_t accumulatedSquaredInterval = totalSquaredInterval;
    unsigned int sampleCount = numSamples;
    totalInterval = 0;
    totalSquaredInterval = 0;
    numSamples = 0;
    interrupts();

    uint32_t mean = accumulatedInterval / sampleCount;
    uint32_t variance = (accumulatedSquaredInterval / sampleCount) - (mean * mean);
    uint32_t standardDeviation = sqrt(variance);

    Serial.print("Mean (us): ");
    Serial.print(mean);
    Serial.print(", Accumulated Squared Interval (us): ");
    Serial.print(accumulatedSquaredInterval);
    Serial.print(", Sample Count: ");
    Serial.print(sampleCount);
    Serial.print(", Mean^2 (us): ");
    Serial.print(mean * mean);
    Serial.print(", Variance (us): ");
    Serial.print(variance);
    Serial.print(", Standard Deviation (us): ");
    Serial.print(standardDeviation);
    Serial.println("");
  }
}

void calculateInterval() {
  unsigned long currentMicros = micros();
  
  if (previousTime) {
    unsigned long interval = currentMicros - previousTime;

    totalInterval += interval;
    totalSquaredInterval += interval * interval;
    numSamples++;
  }

  previousTime = currentMicros;
}

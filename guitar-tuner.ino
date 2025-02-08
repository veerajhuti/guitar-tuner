#include <arduinoFFT.h>

#define MIC A0
#define SAMPLES 128
#define SAMPLING_FREQUENCY 5000


int data[128];
const float guitar_frequencies[] = {82.41, 110.00, 146.83, 196.00, 246.94, 329.63}; // E2, A2, D3, G3, B3, E4
double real[128];
double imaginary[128];
unsigned int period;
unsigned long microseconds;

ArduinoFFT<double> FFT = ArduinoFFT<double>(real, imaginary, SAMPLES, 40);


int getPeakFrequency(double* vReal, int samples) {
  int peakIndex = 0;
  float maxMagnitude = 0;

  for (int i = 1; i < samples / 2; ++i) {
    if (vReal[i] > maxMagnitude) {
      maxMagnitude = vReal[i];
      peakIndex = i;
    }
  }
  return peakIndex;
}

void setup() {
  Serial.begin(115200);

  period = round(1000000*(1.0/SAMPLING_FREQUENCY));

  pinMode(MIC, INPUT);
  
  for (int pin = 2; pin <= 8; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

void loop() {
  for (int i = 0; i < SAMPLES; ++i) {
    microseconds = micros();
    real[i] = analogRead(MIC);
    imaginary[i] = 0;
  
    while(micros() < (microseconds + (1000000 / SAMPLING_FREQUENCY))) {
    } // delay
  }

  FFT.windowing(real, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); 
  FFT.compute(real, imaginary, SAMPLES, FFT_FORWARD);
  FFT.complexToMagnitude(real, imaginary, SAMPLES);

  int peakIndex = getPeakFrequency(real, SAMPLES);
  float peakFrequency = peakIndex * (SAMPLING_FREQUENCY / SAMPLES);

  Serial.print("Peak Frequency: ");
  Serial.println(peakFrequency);

  int closestString = -1;
  float minDiff = 9999;

  for (int i = 0; i < 6; ++i) {
  float diff = abs(guitar_frequencies[i] - peakFrequency);
    if (diff < minDiff) {
      minDiff = diff;
      closestString = i;
    }
  }
  
  for (int i = 0; i < 6; ++i) {
    if (i == closestString) {
      if (minDiff < 3) {
        digitalWrite(i + 2, HIGH);
      } else {
        digitalWrite(8, HIGH);
        digitalWrite(i + 2, LOW);
      }
    } else {
      digitalWrite(i+2, LOW);
    }
  }
  // delay(100);  // Delay to avoid overwhelming the serial monitor

  if (closestString == -1 || minDiff > 5) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);   // Turn off middle LED if the closest string is tuned
  }
}
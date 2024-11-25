#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1(A2);           //xy=265,279
AudioInputAnalog         adc2(A3);           //xy=267,200
AudioAnalyzeRMS          rms1;           //xy=463,316
AudioAnalyzeRMS          rms2;           //xy=459,238
AudioAnalyzeNoteFrequency notefreq1;      //xy=460,201
AudioAnalyzeNoteFrequency notefreq2;      //xy=459,280
AudioConnection          patchCord1(adc2, notefreq2);
AudioConnection          patchCord2(adc2, rms2);
AudioConnection          patchCord3(adc1, notefreq1);
AudioConnection          patchCord4(adc1, rms1);
// GUItool: end automatically generated code


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial) {}
  Serial.println("ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("RMS1: ");
  Serial.println(rms1.read());
  delay(1000);
}

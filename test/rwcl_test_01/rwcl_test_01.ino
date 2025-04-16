#include <MIDIUSB.h>

#define SENSOR      9
#define DETECTED    1
#define UNDETECTED  0

int previous = 0;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void setup() {
  pinMode(SENSOR, INPUT);
  Serial.begin(115200);
}

void loop() {
  int val = digitalRead(SENSOR);

  if (val == DETECTED && previous == UNDETECTED) {
    noteOn(0, 60, 60);
    Serial.println("ON");
  }

  if (val == UNDETECTED && previous == DETECTED) {
    noteOn(0, 60, 0);
    Serial.println("OFF");
  }
  
  previous = val;
  //delay(100);
}

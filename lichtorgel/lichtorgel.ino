#include <DmxSimple.h>

#define ERROR_PIN 6
#define ERROR_LED_BLINK_DURATION 50
#define DMX_PIN 3
#define DMX_CHANNELS 12


byte incommingByte;

byte midiStatus = 0;
byte midiNote = 0;
byte midiVelocity = 0;

byte byteCount = 0;


void setup() {

  // define error led pin
  pinMode(ERROR_PIN, OUTPUT);
  
  // begin reading midi data
  Serial.begin(31250);

  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */
  DmxSimple.usePin(DMX_PIN);

  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you DmxSimple.write() to. */
  DmxSimple.maxChannel(DMX_CHANNELS);
}


void loop() {
  readMidiByte();
}


void readMidiByte() {
  
  if (Serial.available() > 0) {
    
    // read the incoming byte:
    incommingByte = Serial.read();
    
    if (byteCount == 0) {
      midiStatus = incommingByte;
      byteCount = 1;
    } else if (byteCount == 1) {
      midiNote = incommingByte;
      byteCount = 2;
    } else {
      // here we read the last byte of the midi signal
      midiVelocity = incommingByte;
      // here we have a full midi signal composed of 3 bytes
      gotFullMidiData();
      byteCount = 0;
    }
  }
}


void gotFullMidiData() {
  
  // here analyse midi data and do what ever you want
  
  if (midiStatus == 144) {
    // note on
    playNote(midiNote, midiVelocity);
  } else if (midiStatus == 128) {
    // note off
    playNote(midiNote, 0);
  } else {
    errorLed(1000);
  }
  
}


/* send note to dmx */
void playNote(byte note, byte velocity) {
  DmxSimple.write(note-59, velocity);
}


/* error led blinking for the given time in ms */
void errorLed(int duration) {
  int t = 0;
  while (t < duration) {
    digitalWrite(ERROR_PIN, HIGH);
    delay(ERROR_LED_BLINK_DURATION);
    t += ERROR_LED_BLINK_DURATION;
  }
}




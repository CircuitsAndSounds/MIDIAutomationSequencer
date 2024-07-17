#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();


#define  ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
Encoder myEnc(2, 3);

int oldPosition1  = -999;
int newPosition1  = -999;
bool enc_switch_in = 0;
bool oldEncSwitch = 0;
byte scroll = 0;

#define NUM_OUTPUTS 16

#define ENCSW 5
#define CLK 22

byte outputPins[NUM_OUTPUTS] = {23, 25, 28, 4, 27, 29, 31, 30, 26, 11, 9, 24, 47, 50, 52, 48};
boolean outputStates[NUM_OUTPUTS] = {false};  // Initialize array of boolean variables for each output // false = gate, true = trig
unsigned long trigTimerCLK = 0;
unsigned long trigTimers[NUM_OUTPUTS] = {0};

#include <Adafruit_MCP4728.h>
Adafruit_MCP4728 mcp;

void setup() {

  // Initiate MIDI communications, listen to channel 1
  MIDI.begin(1);

  //       Connect the handleNoteOn function to the library,
  //     so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

  // Do the same for NoteOffs
  MIDI.setHandleNoteOff(handleNoteOff);

  MIDI.setHandleControlChange(handleControlChange);


  pinMode(ENCSW, INPUT_PULLUP); //Encoder Button

  pinMode(CLK, OUTPUT); //Encoder Button
  digitalWrite(CLK, LOW);


  for (int i = 0; i < NUM_OUTPUTS; i++) { //SET TO OUTPUTS AND LOW
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
  }

  mcp.begin(); //BEGIN MCP4728 QUAD DAC

}


void loop() {

  hardwareCheck(); 
  midiCheck();

}


void flashLED(int pin, int times) {

  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(100);
  }

  digitalWrite(outputPins[scroll - 1], LOW);
  digitalWrite(outputPins[scroll], HIGH);
}




void hardwareCheck() {


  oldEncSwitch = enc_switch_in;
  enc_switch_in  = !digitalRead(ENCSW);

  newPosition1 = myEnc.read();

  if ((newPosition1 + 2) / 2 < oldPosition1 / 2) {
    oldPosition1 = newPosition1;
    scroll = scroll + 1;

    digitalWrite(outputPins[scroll - 1], LOW);
    digitalWrite(outputPins[scroll], HIGH);

  }

  else if ((newPosition1 - 2) / 2 > oldPosition1 / 2) {
    oldPosition1 = newPosition1;
    scroll = scroll - 1;

    digitalWrite(outputPins[scroll + 1], LOW);
    digitalWrite(outputPins[scroll], HIGH);

  }


  if (scroll >= 16) {
    scroll = 0;
  }

  else if (scroll < 0) {
    scroll = 15;
  }


  if (oldEncSwitch == 0 && enc_switch_in == 1) {

    outputStates[scroll] = !outputStates[scroll];

    if (outputStates[scroll] == false) { //FLASH ONCE FOR GATE
      flashLED(outputPins[scroll], 1);
    }

    else { //FLASH TWICE FOR TRIG
      flashLED(outputPins[scroll], 2);
    }
  }

}


void midiCheck() {

  MIDI.read();


  MIDI.setInputChannel(1);

  if ((trigTimerCLK > 0) && (millis() - trigTimerCLK > 50)) {
    digitalWrite(CLK, LOW); // Set trigger low after 50 msec
    trigTimerCLK = 0;
  }


  for (int i = 0; i < NUM_OUTPUTS; i++) {

    if ((trigTimers[i] > 0) && (millis() - trigTimers[i] > 50)) {
      digitalWrite(outputPins[i], LOW); // Set trigger low after 50 msec
      trigTimers[i] = 0;
    }
  }

}






void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Do whatever you want when a note is pressed.

  // Try to keep your callbacks short (no delays ect)
  // otherwise it would slow down the loop() and have a bad impact
  // on real-time performance.

  switch (pitch) {

    case 0:
      digitalWrite(CLK, HIGH);
      trigTimerCLK = millis();
      break;


    case 1:
      if (outputStates[0] == false) {
        digitalWrite(outputPins[0], HIGH);
      }

      else {
        digitalWrite(outputPins[0], HIGH);
        trigTimers[0] = millis();
      }
      break;


    case 2:
      if (outputStates[1] == false) {
        digitalWrite(outputPins[1], HIGH);
      }

      else {
        digitalWrite(outputPins[1], HIGH);
        trigTimers[1] = millis();
      }
      break;


    case 3:
      if (outputStates[2] == false) {
        digitalWrite(outputPins[2], HIGH);
      }

      else {
        digitalWrite(outputPins[2], HIGH);
        trigTimers[2] = millis();
      }
      break;


    case 4:
      if (outputStates[3] == false) {
        digitalWrite(outputPins[3], HIGH);
      }

      else {
        digitalWrite(outputPins[3], HIGH);
        trigTimers[3] = millis();
      }
      break;


    case 5:
      if (outputStates[4] == false) {
        digitalWrite(outputPins[4], HIGH);
      }

      else {
        digitalWrite(outputPins[4], HIGH);
        trigTimers[4] = millis();
      }
      break;


    case 6:
      if (outputStates[5] == false) {
        digitalWrite(outputPins[5], HIGH);
      }

      else {
        digitalWrite(outputPins[5], HIGH);
        trigTimers[5] = millis();
      }
      break;


    case 7:
      if (outputStates[6] == false) {
        digitalWrite(outputPins[6], HIGH);
      }

      else {
        digitalWrite(outputPins[6], HIGH);
        trigTimers[6] = millis();
      }
      break;


    case 8:
      if (outputStates[7] == false) {
        digitalWrite(outputPins[7], HIGH);
      }

      else {
        digitalWrite(outputPins[7], HIGH);
        trigTimers[7] = millis();
      }
      break;


    case 9:
      if (outputStates[8] == false) {
        digitalWrite(outputPins[8], HIGH);
      }

      else {
        digitalWrite(outputPins[8], HIGH);
        trigTimers[8] = millis();
      }
      break;

    case 10:
      if (outputStates[9] == false) {
        digitalWrite(outputPins[9], HIGH);
      }

      else {
        digitalWrite(outputPins[9], HIGH);
        trigTimers[9] = millis();
      }
      break;

    case 11:
      if (outputStates[10] == false) {
        digitalWrite(outputPins[10], HIGH);
      }

      else {
        digitalWrite(outputPins[10], HIGH);
        trigTimers[10] = millis();
      }
      break;

    case 12:
      if (outputStates[11] == false) {
        digitalWrite(outputPins[11], HIGH);
      }

      else {
        digitalWrite(outputPins[11], HIGH);
        trigTimers[11] = millis();
      }
      break;

    case 13:
      if (outputStates[12] == false) {
        digitalWrite(outputPins[12], HIGH);
      }

      else {
        digitalWrite(outputPins[12], HIGH);
        trigTimers[12] = millis();
      }
      break;

    case 14:
      if (outputStates[13] == false) {
        digitalWrite(outputPins[13], HIGH);
      }

      else {
        digitalWrite(outputPins[13], HIGH);
        trigTimers[13] = millis();
      }
      break;

    case 15:
      if (outputStates[14] == false) {
        digitalWrite(outputPins[14], HIGH);
      }

      else {
        digitalWrite(outputPins[14], HIGH);
        trigTimers[14] = millis();
      }
      break;

    case 16:
      if (outputStates[15] == false) {
        digitalWrite(outputPins[15], HIGH);
      }

      else {
        digitalWrite(outputPins[15], HIGH);
        trigTimers[15] = millis();
      }
      break;

  }

}



void handleNoteOff(byte channel, byte pitch, byte velocity) {
  // Do something when the note is released.
  // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.

  switch (pitch) {

    case 0:
      digitalWrite(CLK, LOW);
      break;

    case 1:
      if (outputStates[0] == false) {
        digitalWrite(outputPins[0], LOW);
      }
      break;

    case 2:
      if (outputStates[1] == false) {
        digitalWrite(outputPins[1], LOW);
      }
      break;

    case 3:
      if (outputStates[2] == false) {
        digitalWrite(outputPins[2], LOW);
      }
      break;

    case 4:
      if (outputStates[3] == false) {
        digitalWrite(outputPins[3], LOW);
      }
      break;

    case 5:
      if (outputStates[4] == false) {
        digitalWrite(outputPins[4], LOW);
      }
      break;

    case 6:
      if (outputStates[5] == false) {
        digitalWrite(outputPins[5], LOW);
      }
      break;

    case 7:
      if (outputStates[6] == false) {
        digitalWrite(outputPins[6], LOW);
      }
      break;


    case 8:
      if (outputStates[7] == false) {
        digitalWrite(outputPins[7], LOW);
      }
      break;

    case 9:
      if (outputStates[8] == false) {
        digitalWrite(outputPins[8], LOW);
      }
      break;

    case 10:
      if (outputStates[9] == false) {
        digitalWrite(outputPins[9], LOW);
      }
      break;

    case 11:
      if (outputStates[10] == false) {
        digitalWrite(outputPins[10], LOW);
      }
      break;

    case 12:
      if (outputStates[11] == false) {
        digitalWrite(outputPins[11], LOW);
      }
      break;

    case 13:
      if (outputStates[12] == false) {
        digitalWrite(outputPins[12], LOW);
      }
      break;

    case 14:
      if (outputStates[13] == false) {
        digitalWrite(outputPins[13], LOW);
      }
      break;

    case 15:
      if (outputStates[14] == false) {
        digitalWrite(outputPins[14], LOW);
      }
      break;

    case 16:
      if (outputStates[15] == false) {
        digitalWrite(outputPins[15], LOW);
      }
      break;
  }
}


void handleControlChange(byte channel, byte number, byte value) {


  if (number == 20) {
    mcp.setChannelValue(MCP4728_CHANNEL_D, value << 5, MCP4728_VREF_VDD, MCP4728_GAIN_2X);
  }

  else if (number == 21) {
    mcp.setChannelValue(MCP4728_CHANNEL_A, value << 5, MCP4728_VREF_VDD, MCP4728_GAIN_2X);
  }

  else if (number == 22) {
    mcp.setChannelValue(MCP4728_CHANNEL_B, value << 5, MCP4728_VREF_VDD, MCP4728_GAIN_2X);
  }

  else if (number == 23) {
    mcp.setChannelValue(MCP4728_CHANNEL_C, value << 5, MCP4728_VREF_VDD, MCP4728_GAIN_2X);
  }


}

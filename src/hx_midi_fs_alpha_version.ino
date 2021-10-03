#include <Bounce2.h>
#include <MIDI.h>

/*--------------------------------------------------------------------
 |  DEFINES
 *-------------------------------------------------------------------*/
#define FS1_PIN A0            // Pin for footswitch1
#define FS2_PIN A1            // Pin for footswitch2
#define DEBOUNCE_TIME 20      // 20 ms debounce time
#define MOD_VALUE 2           // Modulus value
#define FOOTSWITCH_MODE_CC 71 // Footswitch mode CC for the Line 6 HX Stomp
#define MODE_SCROLL 1         // The value for the CC message (preset mode)
#define MODE_SNAPSHOT 3       // the value for the CC message (snapshot mode)
#define TAP_TEMPO_CC 64       // Tap Tempo CC for the Line 6 HX Stomp
#define TAP_TEMPO_VALUE 100   // The value for the Tap Tempo CC message
#define TUNER_CC 68           // Tuner CC for the Line 6 HX Stomp
#define TUNER_VALUE 127       // The value for the Tuner CC message
#define MIDI_CHANNEL 1        // The midi channel to transmit to. Change this to your preference.
#define LONG_PRESS_TIME 1500  // 1500 milliseconds (long press of a footswitch)


/*--------------------------------------------------------------------
 |  VARIABLES
 *-------------------------------------------------------------------*/
int relay = 0;                          // int relay variable. Defaults at 0 but (should) never exceed 1
boolean checkTime = false;              // boolean 
boolean tunerActive = false;            // boolean for checking if the tuner on the HX Stomp is active
boolean footSwitch2Released = false;    // boolean for setting true/false if the footswitch is released
unsigned long pressedTime = 0;          // variable for comparing time (longpress of a footswitch)
unsigned long currentTime = 0;          // variable for comparing time


/*--------------------------------------------------------------------
 |  FOOTSWITCHES
 *-------------------------------------------------------------------*/
Bounce footSwitch1 = Bounce();
Bounce footSwitch2 = Bounce();


/*--------------------------------------------------------------------
 |  MIDI INSTANCE
 |  This calls the function to create the Midi instance. This uses the
 |  default settings of the MIDI.h library. If you have a different 
 |  arduino board you might have to specify what serial port you are using.
 |  
 |  From what I understand this can be achieved using:
 |
 |    MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
 |
 |  I have not tested this so I I need to test this further on other 
 |  Arduino boards as well
 *-------------------------------------------------------------------*/
MIDI_CREATE_DEFAULT_INSTANCE();         


/*--------------------------------------------------------------------
 |  FUNCTIONS
 *-------------------------------------------------------------------*/
 
/**
 *  updateRelay()
 *  This function is needed for turning the momentary footswitch into
 *  behaving like a latching switch. It's basically adding + 1 to 
 *  whatever value relay has.
 *  I'm using a modulus value so that the value never exceeds 1.
 *  This should mean that the relay variable is always a value between
 *  0 and 1. This behaves like a on-off or true-false.
 *  This function gets called when the footSwitch1 is pressed.
 */
void updateRelay() {
  relay = (relay + 1) % MOD_VALUE;  // changes the value of relay between 0 and 1
}


// ==================================================
// Function for switching between footswitch modes
// It uses a switch case and the relay variable to 
// switch between preset and snapshot mode.
// in any case of error it defaults to preset mode.
// ==================================================

/**
 *  setFootSwitchMode()
 *  This function gets called when footSwitch1 is released.
 */
void setFootswitchMode() {
  switch(relay) {
    case 0: // if relay value is 0, it should set the footswitch mode to preset
      //Serial.println("Footswitch mode set to preset!");
      MIDI.sendControlChange(FOOTSWITCH_MODE_CC,MODE_SCROLL, MIDI_CHANNEL);
      break;
    case 1: // if the relay value is 1, it should set the footswitch mode to snapshot
      //Serial.println("Footswitch mode set to snapshot!");
      MIDI.sendControlChange(FOOTSWITCH_MODE_CC,MODE_SNAPSHOT, MIDI_CHANNEL);
      break;
    default:  // in case anything goes wrong, set the relay to 0
      relay = 0;
      //Serial.println("ERROR reading relay value: Set the footswitch mode to preset!");
      MIDI.sendControlChange(FOOTSWITCH_MODE_CC,MODE_SCROLL, MIDI_CHANNEL);
      break;
  }
}

/**
 *  activateTuner()
 *  This method is very simply and simply sends a CC (68) message with the
 *  value of 127. This turns on the tuner on the HX Stomp.
 */
void activateTuner() {
  MIDI.sendControlChange(TUNER_CC,TUNER_VALUE, MIDI_CHANNEL);
}

/**
 *  deactivateTuner()
 *  This function is identical to activateTuner() but I gave it a different
 *  name to make the code more readable.
 */
void deactivateTuner() {
  MIDI.sendControlChange(TUNER_CC,TUNER_VALUE, MIDI_CHANNEL);
}

/**
 *  sendTapTempo()
 *  This function is for sending a Tap Tempo CC message with a fixed value
 */
void sendTapTempo() {
  MIDI.sendControlChange(TAP_TEMPO_CC,TAP_TEMPO_VALUE, MIDI_CHANNEL);
}



/*--------------------------------------------------------------------
 |  setup
 *-------------------------------------------------------------------*/
void setup() {
  /* setting the pinMode on the pins for the footswitches */
  //pinMode(A0, INPUT_PULLUP);
  //pinMode(A1, INPUT_PULLUP);

  footSwitch1.attach(FS1_PIN, INPUT_PULLUP);  // attach the debouncer to pin with INPUT_PULLUP mode
  footSwitch2.attach(FS2_PIN, INPUT_PULLUP);  // attach the debouncer to pin with INPUT_PULLUP mode

  footSwitch1.interval(DEBOUNCE_TIME);  // Use a debounce interval of 20 milliseconds
  footSwitch2.interval(DEBOUNCE_TIME);  // Use a debounce interval of 20 milliseconds

  MIDI.begin(MIDI_CHANNEL_OFF); // MIDI_CHANNEL_OFF means we are not listening to incomming MIDI
}


/*--------------------------------------------------------------------
 |  main loop
 *-------------------------------------------------------------------*/
void loop() {

  footSwitch1.update();
  footSwitch2.update();

  if (footSwitch1.changed()) {
    if (footSwitch1.read() == HIGH) {
      updateRelay();
    }

    if (footSwitch1.read() == LOW) {
      setFootswitchMode();
    }
  }

  if (footSwitch2.changed()) {
    if (footSwitch2.read() == HIGH) {
      if (footSwitch2.previousDuration() > 1500) {
        activateTuner();
        tunerActive = true;
      } else {
        tunerActive = false;
      }
    }

    if (footSwitch2.read() == LOW) {
      if (!tunerActive) {
        sendTapTempo();
      }
    }
  }
}
/*--------------------------------------------------------------------
 |  DEFINES
 *-------------------------------------------------------------------*/
#define FS1_PIN A0            // Pin for footswitch1
#define FS2_PIN A1            // Pin for footswitch2
#define DEBOUNCE_TIME 20      // 20 ms debounce time
#define MOD_VALUE 3           // Modulus value
#define FOOTSWITCH_MODE_CC 71 // Footswitch mode CC for the Line 6 HX Stomp
#define MODE_STOMP 0          // The value for the CC message (stomp mode)
#define MODE_SCROLL 1         // The value for the CC message (scroll mode)
#define MODE_PRESET 2         // The value for the CC message (preset mode)
#define MODE_SNAPSHOT 3       // the value for the CC message (snapshot mode)
#define MODE_NEXT 4           // The value for the CC message (next mode)
#define MODE_PREVIOUS 5       // The value for the CC message (previous mode)
#define TAP_TEMPO_CC 64       // Tap Tempo CC for the Line 6 HX Stomp
#define TAP_TEMPO_VALUE 100   // The value for the Tap Tempo CC message
#define TUNER_CC 68           // Tuner CC for the Line 6 HX Stomp
#define TUNER_VALUE 127       // The value for the Tuner CC message
#define MIDI_CHANNEL 1        // The midi channel to transmit to. Change this to your preference.
#define LONG_PRESS_TIME 1500  // 1500 milliseconds (long press of a footswitch)


/*--------------------------------------------------------------------
 |  INCLUDES
 *-------------------------------------------------------------------*/
#include <Bounce2.h>
#include <MIDI.h>


/*--------------------------------------------------------------------
 |  VARIABLES
 *-------------------------------------------------------------------*/
int footswitchMode = 0;                 // for selecting footswitch mode on the HX Stomp
boolean tunerIsActivated = false;       // for checking if the tuner on the HX Stomp is active


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
 |  I have not tested this so I need to test this further on other 
 |  Arduino boards as well
 *-------------------------------------------------------------------*/
MIDI_CREATE_DEFAULT_INSTANCE();         


/*--------------------------------------------------------------------
 |  FUNCTIONS
 *-------------------------------------------------------------------*/

 /**
 *  setFootSwitchMode()
 *  This function gets called when footSwitch1 is released.
 *  It basically sets a variable to three possible values: 0, 1 and 2.
 *  This is needed later on to set the necessary footswitch mode of the HX Stomp.
 */
void setFootswitchMode() {
  //Serial.println("setting footswitch mode");
  footswitchMode = (footswitchMode + 1) % MOD_VALUE;  // 0, 1, 2
}

/**
 *  updateHxFootswitchMode()
 *  This function is for updating the footswitch mode on the HX Stomp.
 *  I'm only changing between scroll, stomp and snapshot mode but you could
 *  go through all 4 modes if you wanted to.
 *  This function gets called when the footSwitch1 is released.
 */
void updateHxFootswitchMode() {
  switch(footswitchMode) {
    case 0: // SCROLL MODE
      //Serial.println("Footswitch mode set to scroll!");
      MIDI.sendControlChange(FOOTSWITCH_MODE_CC,MODE_SCROLL, MIDI_CHANNEL);
      break;
      
    case 1: // STOMP MODE
      //Serial.println("Footswitch mode set to stomp");
      MIDI.sendControlChange(FOOTSWITCH_MODE_CC,MODE_STOMP, MIDI_CHANNEL);
      break;
      
    case 2: // SNAPSHOT MODE
      //Serial.println("Footswitch mode set to snapshot!");
      MIDI.sendControlChange(FOOTSWITCH_MODE_CC,MODE_SNAPSHOT, MIDI_CHANNEL);
      break;
      
    default:  // in case anything goes wrong
      footswitchMode = 0;
      //Serial.println("ERROR reading relay value: Set the footswitch mode to Scroll!");
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
    //Serial.println("Activacting the Tuner!");
    MIDI.sendControlChange(TUNER_CC,TUNER_VALUE, MIDI_CHANNEL);
  }


/**
 *  deactivateTuner()
 *  This function is identical to activateTuner() but I gave it a different
 *  name to make the code more readable.
 */
void deactivateTuner() {
  //Serial.println("Deactivating the Tuner!");
  MIDI.sendControlChange(TUNER_CC,TUNER_VALUE, MIDI_CHANNEL);
}


/**
 *  sendTapTempo()
 *  This function is for sending a Tap Tempo CC message with a fixed value
 */
void sendTapTempo() {
  //Serial.println("Sending Tap Tempo");
  MIDI.sendControlChange(TAP_TEMPO_CC,TAP_TEMPO_VALUE, MIDI_CHANNEL);
}


/*--------------------------------------------------------------------
 |  setup
 *-------------------------------------------------------------------*/
void setup() {
  //Serial.begin(115200); // for debugging

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

  // update state of footswitches
  footSwitch1.update();
  footSwitch2.update();

  //===============================
  // FOOTSWITCH 1
  //===============================
  if (footSwitch1.changed()) {
    
    if (footSwitch1.read() == LOW) {
      //Serial.println("FS1 pressed");
      setFootswitchMode();
    }

    if (footSwitch1.read() == HIGH) {
      //Serial.println("FS1 released");
      updateHxFootswitchMode();
    }
  }


  //===============================
  // FOOTSWITCH 2
  //===============================

  // if detecting a long press
  // activate the tuner
  if (footSwitch2.read() == LOW && footSwitch2.currentDuration() >= LONG_PRESS_TIME) {
    if (!tunerIsActivated) {
      activateTuner();
      tunerIsActivated = true;
    }
  }

  // using the changed() function makes sure that the code here is only run
  // once when a change of state has been detected.
  if (footSwitch2.changed()) {
   
    if (footSwitch2.read() == HIGH) {
      //Serial.println("FS2 released");

      // NOT USED BUT KEPT TO SHOW EXAMPLE
      // checking for long press
      //if (footSwitch2.previousDuration() > 1500) {
      //  Serial.println("FS2 was long pressed");
      //}

      // checking for short press
      if (footSwitch2.previousDuration() < 1500) {
        //Serial.println("FS2 was short pressed");

        // if the tuner is not activated
        if (!tunerIsActivated) {
          sendTapTempo(); // send the tap tempo
        }

        // if the tuner was activated
        if (tunerIsActivated) {
          // turn it off
          deactivateTuner();
          tunerIsActivated = false;
        }
      }
    }
  }
}
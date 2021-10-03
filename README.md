# HX Stomp Midi Footswitch #

## Building a DIY Midi footswitch pedal for the Line 6 HX Stomp ##

### Introduction ###

While the HX Stomp is a great amp modeler for guitar and bass players, it only has 3 buttons and the usage of an expression pedal limits the possibilities of adding more footswitches. 
I wanted the ability to change presets but still be able to activate/deactivate multiple effects using Snapshot Mode. This cannot be achieved unless you physically change the mode using the buttons on the HX Stomp. Reading the manual, I understood that a footswitch could solve this. I looked at products that might be a solution but found them to either be expensive or having too many buttons. Based upon my own personal needs for a powerful and small midi pedal, I decided build my own a midi pedal to extend usability of the HX Stomp. This repository is a way for me to share my findings and explain how I created my DIY midi footswitch using off-the-shelf components. The libraries used (and needed) for the Arduino Nano are the [Midi library](https://github.com/FortySevenEffects/arduino_midi_library) and [Bounce2](https://github.com/thomasfredericks/Bounce2). Both can be installed using the Arduino IDE.

### The Pedal & Features ###

The midi footswitch uses a (cheap copy) Arduino Nano as the main unit for reading footswitch presses and sending corresponding midi messages to the HX Stomp. On top of the pedal there are two footswitches. The top footswitch acts as a latching switch (despite being momentary) changing the footswitch mode on the HX Stomp between **Scroll Mode** and **Snapshot Mode**.
It features two DC power connectors. The first DC socket is for accepting the stock 9volt power supply included with the HX Stomp. This provides the Arduino Nano with voltage. The second DC socket is used for forwarding 9 volts to the HX Stomp using a DC patch cable. This removes the need for a separate power supply.
While the pedal is set to only send certain midi messages, there is nothing stopping you from changing this and have it do whatever you want.

### The Logic ###

TODO



### BOM ###

For creating this pedal you need the following parts

* 2 x SPST Momentary Footswitch
* 1 x Pedal Enclosure (1590B or 1590BB)
* 1 x Arduino Nano v3
* 2 x DC Power Connector (Barrel Plug)
* 1 x 5 pin DIN Socket (MIDI)

The latest version of [Midi library](https://github.com/FortySevenEffects/arduino_midi_library) and [Bounce2](https://github.com/thomasfredericks/Bounce2)

### Credits & Thanks ###

These people helped me, in some way or other, to complete the project.

Thanks to Erikson Silva for inspiring me to build my own midi footswitch and recommending a suitable debounce time of 20ms for the footswitches based on extensive testing that he did prior to me starting this project. This saved me hours of testing.

Thanks to the Hacker Shack YouTube channel for recommending the usage of the [Bounce2](https://github.com/thomasfredericks/Bounce2) library for Arduino. It reduces the issues of the noise when pressing the footswitches and makes the pedal more reliable. The video can be seen [here](https://www.youtube.com/watch?v=M25I58I7BtI)

Thanks to Jason Sadites for sharing a video on YouTube, explaining how to send midi messages to the Line 6 HX Stomp. In the video he explains how to (using only one footswitch) activate the Tuner and send Tap Tempo messages. Although the video was a instructional video for the Morningstar MC6 MkII, this gave me the idea to implement my way to do this with the Arduino Nano. This was done by having the code read footswitch presses as a regular press and long press. The video can be seen [here](https://www.youtube.com/watch?v=en8YLGcwuPc)

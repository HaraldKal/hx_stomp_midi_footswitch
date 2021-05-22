# HX Stomp Midi Footswitch #

## Building a DIY Midi footswitch pedal for the Line 6 HX Stomp ##

### Introduction ###

While the HX Stomp is a great amp modeler for guitar and bass players, it only has 3 buttons and the usage of an expression pedal limits the possibilities of adding more footswitches. I looked at products that might be a solution but found them to either be expensive or having too many buttons. Based upon my own personal needs I decided build my own a midi footswitch to extend usability of the HX Stomp. This repository is a way for me to share my findings and explain how I created my DIY midi footswitch using off-the-shelf components.

### The Pedal & Features ###

The pedal uses two footswitches, one acting as a latching switch changing the footswitch mode on the HX Stomp between **Scroll Mode** and **Snapshot Mode**
It features two DC power connectors for accepting a 9volt power supply. That voltage can be forwarded to the HX Stomp using a DC patch cable, thus removing the need for a separate power supply.
The brain of the pedal is a (cheap copy) Arduino Nano. I chose this because it can receive voltages between 7-12 volts and would suffice for this project. It also outputs 5 volt that is needed for sending Midi messages to the HX Stomp.

### The Logic ###



### BOM ###

For creating this pedal you need the following parts

* 2 x SPST Momentary Footswitch
* 1 x Pedal Enclosure (1590B or 1590BB)
* 1 x Arduino Nano v3
* 2 x DC Power Connector (Barrel Plug)
* 1 x 5 pin DIN Socket (MIDI)

### Credits ###

These people helped, in some way or other, me to complete the project.

Thanks to Erikson Silva for inspiring me to build my own midi footswitch and recommending a suitable debounce time of 20ms for the footswitches based on extensive testing that he did prior to me starting this project. This saved me hours of testing.

Thanks to the Hacker Shack YouTube channel for recommending the usage of the Arduino library Bounce2 for reducing noise when pressing the footswitches. The video can be seen [here](https://www.youtube.com/watch?v=M25I58I7BtI)

Thanks to Jason Sadites for sharing a video on YouTube, explaining how to send midi messages to the Line 6 HX Stomp. In the video he explains how to (using only one footswitch) activate the Tuner and send Tap Tempo messages. Although the video was a instructional video for the Morningstar MC6 MkII, this gave me the idea to find a way to do this with the Arduino Nano by having the code read footswitch presses as a regular press and long press. The video can be seen [here](https://www.youtube.com/watch?v=en8YLGcwuPc)

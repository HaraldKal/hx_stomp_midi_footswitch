# HX Stomp Midi Footswitch #

## Building a DIY Midi footswitch pedal for the Line 6 HX Stomp ##

### Description ###

This is my implementation for a midi pedal to switch between footswitch modes on the HX Stomp and be able to Tap Tempo and activate the tuner despite of being in Snapshot Mode on the HX Stomp.
It features two DC power connectors for accepting a 9volt power supply. That voltage can be forwarded to the HX Stomp using a DC patch cable, thus removing the need for a separate power supply.
The brain of the pedal is a (cheap copy) Arduino Nano. I chose this because it can receive voltages between 7-12 volts and would suffice for this project. It also outputs 5 volt that is needed for sending Midi messages to the HX Stomp.

![alt text]("https://raw.githubusercontent.com/HaraldKal/hx_stomp_midi_footswitch/main/images/pedal-side.jpg" "Picture of the pedal")

### BOM ###

For creating this pedal you need the following parts

* 2 x SPST Momentary Footswitch
* 1 x Pedal Enclosure (1590B or 1590BB)
* 1 x Arduino Nano v3
* 2 x DC Power Connector (Barrel Plug)
* 1 x 5 pin DIN Socket (MIDI)

### Credits ###

These people helped in some way or other me to complete the project.

Thanks to Erikson Silva for inspiring me to build my own midi footswitch and recommending a suitable debounce time of 20ms for the footswitches based on extensive testing that he did prior to me building my own. This saved me hours of testing.

Thanks to Jason Sadites for sharing a video on YouTube, explaining how to send midi messages to the Line 6 HX Stomp. In the video he explains how to (using only one footswitch) activate the Tuner and send Tap Tempo messages. Although the video was a instructional video for the Morningstar MC6 MkII, this gave me the idea to find a way to do this with the Arduino Nano by having the code read footswitch presses as a regular press and long press

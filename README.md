# HX Stomp Midi Footswitch #

## A DIY Midi footswitch pedal for the Line 6 HX Stomp ##

### Description ###

This is my implementation for a midi pedal to switch between footswitch modes on the HX Stomp and be able to Tap Tempo and activate the tuner despite of being in Snapshot Mode on the HX Stomp.
It features two DC power connectors for accepting a 9volt power supply. That voltage can be forwarded to the HX Stomp using a DC patch cable, thus removing the need for a separate power supply.
The brain of the pedal is a (cheap copy) Arduino Nano. I chose this because it can receive voltages between 7-12 volts and would suffice for this project. It also outputs 5 volt that is needed for sending Midi messages to the HX Stomp.

<img src=https://raw.githubusercontent.com/HaraldKal/hx_stomp_midi_footswitch/main/images/pedal side.jpg" 
  alt="Picture of Midi pedal from the side" title="Midi pedal" align="center" width="100%" />

### BOM ###

For creating this pedal you need the following parts

* 2 x SPST Momentary Footswitch
* 1 x Pedal Enclosure (1590B or 1590BB)
* 1 x Arduino Nano v3
* 2 x DC Power Connector (Barrel Plug)
* 1 x 5 pin DIN Socket (MIDI)

# Arduino-AudioSwitchPower
**Audio switch for 4 stereo channels of power.**

![](https://github.com/Democrito/Arduino-AudioSwitchPower/blob/main/scheme/scheme_v5.PNG)

This is a 4 channel stereo power switch. This type of switch is very expensive and difficult to find on the market. With the help of an Arduino and some relays we can make one at a very low cost.

You can select a pair of speakers from the 4 possible stereo channels. It is designed for high power, which is why it has relays.

The common inputs + L, -L, + R & -R must be connected to the power amplifier. The channel outputs must go to the loudspeakers. Being stereo, they are separated by channels and the corresponding L & Rs.

The operation is very simple, with an encoder we select the channel, press the encoder and that channel will be selected. The 4 LEDs will help us to visualize the selected channel and the channel that we are traveling at that moment. When a channel is selected, the corresponding led will remain on, and if we move the encoder to another channel, the led will blink. Only one channel will be activated at a time. When you activate a channel (and the LEDs will represent it) you can deactivate it by clicking on the same channel again.

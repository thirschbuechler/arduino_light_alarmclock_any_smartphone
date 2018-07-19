# arduino_light_alarmclock_any_smartphone
ESP based Light Alarmclock, triggerable by (probably) any playlist-capable smartphone alarm clock

To better wake up at odd times, especially in dark winter or with blinds down, I wanted an alarm clock which can be controlled by any smartphone alarm app which supports playlists.

The basic idea is to make a reroute to a playlist (i.e. BBC radio) and mute it, and trigger the alarm when the reroute is called.

For this I used a ESP-based Geekcreit Nodemcu MCU, but programmed it with the Arduino Interface.
Afterwards any arduino relais board, connected via rainbowcolored dupont wires, can trigger lamps etc.

## Caution: Mains Voltage (240V/120V) can kill you! Only use 12V led-stripes if you're not familiar with that.

In any case, i'd suggest housing it in a IP54-rated mains electric container and changing the obviously bad wifi credentials in the code before flashing.

At last, define a static IP on your router for this device and use your Smartphone Alarmclock App (e.g. AlarmDroid) and enter http://deviceIP/x.pls, where x stands for relays 1-4 like stated in the code. Now make multiple mute alarms which end automatically to trigger the different relays and their linked lamps.

(Alternatively, call http://deviceIP/x.pls in your browser to toggle them)

# arduino_light_alarmclock_any_smartphone
ESP based Light Alarmclock, triggerable by (probably) any playlist-capable smartphone (i.e. Android/Iphone/Windows) alarm clock

To better wake up at odd times, especially in dark winter or with blinds down, I wanted an alarm clock which can be controlled by any smartphone alarm app which supports playlists.

The basic idea is to make a reroute to a playlist (i.e. BBC radio) and mute it, and trigger the alarm when the reroute is called.

For this I used a ESP-based Geekcreit Nodemcu MCU, but programmed it with the Arduino Interface.
Afterwards any arduino relais board, connected via rainbowcolored dupont wires, can trigger lamps etc.

## Caution: Mains Voltage (240V/120V) can kill you! Only use 12V led-stripes if you're not familiar with that.

In any case, i'd suggest housing it in a plastic IP54-rated mains electric container and changing the obviously bad wifi credentials in the code before flashing. Metal cans woud need to have at least one plastic lid so some RF can come out (2.4 / 5GHz Wifi is RF and can be trapped in a metal can otherwise, i.e. faraday cage, if fully enclosed.

At last, define a static IP on your router for this device and use your Smartphone Alarmclock App (e.g. AlarmDroid) and enter http://deviceIP/x.pls, where x stands for relays 1-4 like stated in the code. Now make multiple mute alarms which end automatically to trigger the different relays and their linked lamps.

(Alternatively, call http://deviceIP/x.pls in your browser to toggle them)

## Smartphone Alarmclock Setup

![overview](https://user-images.githubusercontent.com/8376996/43305052-93323978-9176-11e8-8cd3-891a2171ea0a.png)

![one_alarm_ed](https://user-images.githubusercontent.com/8376996/43305051-93151da2-9176-11e8-84dd-5d43aa3b7585.png)

## Hardware Setup

![camerazoom-20180228214913047](https://user-images.githubusercontent.com/8376996/43304308-e1985e9c-9173-11e8-9afc-8e8a4389d6fb.jpg)

![camerazoom-20180311184126773](https://user-images.githubusercontent.com/8376996/43304311-e3d520aa-9173-11e8-8610-78e8fb049efd.jpg)
The larger case always wins. Always.
![nodemcudevkit_v1-0_io_edited](https://user-images.githubusercontent.com/8376996/43304379-2fe046a0-9174-11e8-8d53-1decdfd07fac.png)


If you're looking for something that runs on its own (i.e. internal clock, configured via web-interface), this seems promising: https://www.instructables.com/id/Wake-up-Ceiling-Light/#discuss

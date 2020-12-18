# IOT LED Advent Wreath

This program is a dynamic Advent Wreath it checks the Google Time Server for the actual day, month and year. With this inforamation it calcs all advent days in the actual year, and power on for any advent a led.

<p align="center">
  <span>English</span> |
  <a href="https://github.com/lucki1000/Advent_ESP/blob/main/lang/readme_de.md">German</a>
</p>

# Content:
- [What is this Project for?](#whatsthis)
- [How to use it?](#howtouseit)
  - [What you need to change](#changes)
  - [Compiling and Flash to ESP](#compileandflash)

## What's this Project?<a name="whatsthis"></a>

I've made this Project, because i'm to lazy to fire on the 4 candles of my advent wreath every year.:wink:

The really reason is learned many things of ESP boards and the Arduino IDE also C++, and if you are good at handcrafting, you can make a nice LED Advent Wreath. I think you can use it on any board who can use this module: <ESP8266WiFi.h>.

## How to use it?<a name="howtouseit"></a>

Download and Flash it to your device.

## What you need to change<a name="changes"></a>

What you absolutly must change are this lines:
```
//WiFi setup
const char ssid[] = "SSID";
const char pass[] = "WLAN KEY";
```
cause otherwise it hangs in a while loop and print "." into the serial monitor, and waits for connection. 

If you would like to change the NTP Server or the Timezone you have to change this lines:
```
//NTP Server
static const char ntpServerName[] = "time.google.com";
//Set Timezone
const int timeZone = 1; //Central European Time
```

For the used GPIOs you must change:
```
//Set UP lights on GPIOs
const int first_led = 16;
const int second_led = 5;
const int third_led = 4;
const int fourth_led = 0;
```

## Compiling and Flash to ESP<a name="compileandflash"></a>

There is no prebuild binary for you, cause I don't know your Router SSID or WLan Key.
I used the Arduino IDE with a NodeMCU ESP8266, here you have 2 ways to compile this code.
1. you copy the content of my .cpp file and paste it into your sketch.
2. you rename my .cpp file to anythingwhatuwant.ino, important is that .ino you can add it after .cpp or replace it.

Then I wish you good luck, errors or issues you can report in the issue section of this repo.
